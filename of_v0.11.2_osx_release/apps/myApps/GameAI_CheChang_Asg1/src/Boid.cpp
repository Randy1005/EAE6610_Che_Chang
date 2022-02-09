//
//  Boid.cpp
//  GameAI_CheChang_Asg1
//
//  Created by 張哲 on 2/4/22.
//
#include "Boid.hpp"

Boid::Boid(float i_posx, float i_posy, float i_radius, float i_orientation, ofColor i_color, float i_window_width, float i_window_height) {
    this->rigid_body.position = ofVec2f(i_posx, i_posy);
    this->radius = i_radius;
    this->rigid_body.orientation = i_orientation;
    this->color = i_color;
    this->nose_length_ = 2 * this->radius;
    this->app_window_width = i_window_width;
    this->app_window_height = i_window_height;
    
    
}

void Boid::Draw() {
    // draw breadcrumbs
    for (size_t i = 0; i < breadcrumbs.size(); i++) {
        if (breadcrumbs[i])
            breadcrumbs[i]->Draw();
    }
    
    ofPushMatrix();
    // translate coords to the boid's position
    ofTranslate(rigid_body.position.x, rigid_body.position.y);
    
    // rotate coords to the boid's orientation
    ofRotateZDeg(GetOrientationInDegrees());
    
    ofSetLineWidth(DRAW_STROKE);
    ofSetColor(color);
    ofDrawCircle(0, 0, radius);
    ofSetColor(color);
    ofDrawTriangle(0, radius, 0, -radius, nose_length_, 0);

    ofPopMatrix();
}

void Boid::Update() {
    
    // angular velocity update
    rigid_body.angular_velocity += rigid_body.angular_acceleration;
    
    // orientation update
    rigid_body.orientation += rigid_body.angular_velocity;
    
    
    // velocity update
    rigid_body.velocity += rigid_body.linear_acceleration;
    
    // position update
    rigid_body.position += rigid_body.velocity;
    
    // instantiate/update breadcrumb positions
    if (timer-- <= 0) {
        timer = INTERVAL_BREADCRUMB;
        
        if (breadcrumb_index++ < MAX_BREADCRUMBS) {
            breadcrumbs.push_back(new BreadCrumb(rigid_body.position.x, rigid_body.position.y, 2.0f, ofColor::blueSteel));
        }
        else {
            // reuse the already instantiated breadcrumbs,
            // just update their positions
            breadcrumbs[breadcrumb_index % MAX_BREADCRUMBS]->position = rigid_body.position;
            
            // if the breadcrumb indes becomes too big, set it back
            // to MAX_BREADCRUMS + 1
            if (breadcrumb_index > 60000) {
                breadcrumb_index = MAX_BREADCRUMBS + 1;
            }
            
        }
    }
}

// simple demo that moves the boid along the edge
ofVec2f Boid::MoveAlongWindowEdge() {
    if (rigid_body.position.x < 50 && rigid_body.position.y >= 50) {
        return ofVec2f(0.0f, -3.0f);
    } else if (rigid_body.position.x >= 50 || rigid_body.position.y < 50) {
        if (rigid_body.position.x < app_window_width - 50) {
            return ofVec2f(3.0f, 0.0f);
        } else if (rigid_body.position.x >= app_window_width - 50) {
            return ofVec2f(0.0f, 3.0f);
        }
    }
    
}

DynamicSteeringOutput Boid::Seek(ofVec2f i_target_pos, float i_max_linear_acceleration, float i_max_speed, float i_slow_radius, float i_target_radius, float i_time_to_target) {
    
    float target_speed;
    ofVec2f target_direction = i_target_pos - rigid_body.position;
    float distance = target_direction.length();
    target_direction.normalize();
    
    // case 1: if distance > slow radius, accelerate to max speed
    if (distance > i_slow_radius) {
        target_speed = i_max_speed;
    } else if (distance > i_target_radius && distance <= i_slow_radius) {
        target_speed = ((distance - i_target_radius) / (i_slow_radius - i_target_radius)) * i_max_speed;
        
    } else if (distance <= i_target_radius) {
        target_speed = 0;
    }
    
    // then accelerate to target velocity difference
    ofVec2f velocity_difference = target_speed * target_direction - rigid_body.velocity;
    ofVec2f linear_acceleration = velocity_difference / i_time_to_target;
    if (linear_acceleration.length() > i_max_linear_acceleration) {
        linear_acceleration.normalize();
        linear_acceleration *= i_max_linear_acceleration;
    }
    
    // rotate to the moving direction
    // rigid_body.orientation = ofVec2f(1.0, 0).angle(rigid_body.velocity) * PI / 180.0f;

    
    DynamicSteeringOutput result;
    result.linear_acceleration = linear_acceleration;
    result.angular_acceleration = 0.0f;
    return result;
}

DynamicSteeringOutput Boid::Flee(ofVec2f i_target_pos, float i_max_linear_acceleration) {
    DynamicSteeringOutput result;
    result.linear_acceleration = rigid_body.position - i_target_pos;
    result.linear_acceleration.normalize();
    result.linear_acceleration *= i_max_linear_acceleration;
    result.angular_acceleration = 0.0f;
    return result;
}

DynamicSteeringOutput Boid::Evade(RigidBody i_target_rb, float i_personal_radius, float i_max_linear_acceleration, float i_decay) {
    float distance = (i_target_rb.position - rigid_body.position).length();
    // case 1: target is outside personal radius, linear accel = 0
    
    // case 2: if the target is within personal radius
    float repulsion, strength;
    if (distance <= i_personal_radius) {
        repulsion = i_decay / (distance * distance);
        
    } else {
        // i_max_linear_acceleration = 0;
    }
    
    strength = min(repulsion, i_max_linear_acceleration);
    
    return Flee(i_target_rb.position, strength);
    
}

DynamicSteeringOutput Boid::Align(float i_target_orientation, float i_max_angular_velocity, float i_max_angular_acceleration, float i_slow_angle, float i_target_angle, float i_time_to_target) {
    float angle_diff = i_target_orientation - rigid_body.orientation;
    // normalize to [-PI, PI]
    angle_diff = MapOrientationToRange(angle_diff);
    
    float angle_magnitude = abs(angle_diff);
    
    DynamicSteeringOutput result;
    float target_angular_velocity;
    // if we've reached the target orientation, set angular acceleration = 0
    if (angle_magnitude < i_target_angle) {
        target_angular_velocity = 0.0f;
    } else if (angle_magnitude > i_slow_angle) {
        target_angular_velocity = i_max_angular_velocity;
    } else {
        target_angular_velocity = i_max_angular_velocity * angle_magnitude / i_slow_angle;
    }
    
    // get the signed rotation
    target_angular_velocity *= (angle_diff / angle_magnitude);
    
    // accelerate to target angulat velocity
    result.angular_acceleration = target_angular_velocity - rigid_body.angular_velocity;
    result.angular_acceleration /= i_time_to_target;
    
    // clamp to max angular acceleration
    float angular_acceleration_magnitude = abs(result.angular_acceleration);
    if (angular_acceleration_magnitude > i_max_angular_acceleration) {
        result.angular_acceleration /= angular_acceleration_magnitude;
        result.angular_acceleration *= i_max_angular_acceleration;
    }
    
    result.linear_acceleration = ofVec2f(0, 0);
    return result;
    
}

DynamicSteeringOutput Boid::LookWhereYoureGoing() {
    // check for zero direction
    if (rigid_body.velocity.length() == 0)
        return;
    
    float target_orientation = atan2(-rigid_body.velocity.x, rigid_body.velocity.y);
    
    // delegate to Align
    return Align(target_orientation, 0.02f, 0.005f, 1.5f, 0.3f, 5.0f);
}


DynamicSteeringOutput Boid::Wander(float i_wander_radius, float i_wander_rate, float i_max_linear_acceleration) {
    // get a random angle
    float target_orientation = rigid_body.orientation + ofRandom(-1.0f, 1.0f) * i_wander_rate;
    // get a random target position located on the circumference
    ofVec2f target_pos = ofVec2f(cos(target_orientation) * i_wander_radius, sin(target_orientation) * i_wander_radius) + rigid_body.position;
    
    DynamicSteeringOutput result;
    result.linear_acceleration = Seek(target_pos, i_max_linear_acceleration, 1.0f, 20, 10, 1.0f).linear_acceleration;
    result.angular_acceleration = LookWhereYoureGoing().angular_acceleration;
    
    return result;
}

float Boid::MapOrientationToRange(float i_orientation) {
    float mapped_orientation = fmod(i_orientation + PI, 2 * PI);
    if (mapped_orientation < 0)
        mapped_orientation += 2 * PI;
    return mapped_orientation - PI;
}






float Boid::GetOrientationInDegrees() {
    // don't know why there's a 90 degree diff, so I had to offset this manually
    return (rigid_body.orientation * 180.0f) / PI + 90;
}





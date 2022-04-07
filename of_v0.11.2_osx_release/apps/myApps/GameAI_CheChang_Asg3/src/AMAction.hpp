//
//  AMAction.hpp
//  GameAI_CheChang_Asg1
//
//  Created by 張哲 on 4/5/22.
//

#ifndef AMAction_hpp
#define AMAction_hpp

/**
 ActionManager action node, for Behavior Tree nodes and Decision Tree nodes to inherit
 so we can store these AM action into action manager
 */
struct AMAction {
    AMAction();
    int priority;
    float queued_time;
    float expiry_time;
    
    // bool can_interrupt() const;
    // bool can_do_both(AMAction* i_action) const;
    bool is_complete() const;
    void execute();
    
};

#endif /* AMAction_hpp */

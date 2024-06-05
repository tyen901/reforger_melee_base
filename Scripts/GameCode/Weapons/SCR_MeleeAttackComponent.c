/*!
\addtogroup Weapon
\{
*/

class SCR_MeleeAttackComponentClass: ScriptComponentClass
{
}

class SCR_MeleeAttackComponent: ScriptComponent
{
    InputManager m_InputManager;
    IEntity m_owner;
    IEntity m_Player;

    override void OnPostInit(IEntity owner)
    {
        m_owner = owner;
        m_InputManager = GetGame().GetInputManager();
        owner.SetFlags(EntityFlags.ACTIVE, false);
        SetEventMask(owner, EntityEvent.FRAME);
        int mask = GetEventMask();
    }

    override void EOnActivate(IEntity owner)
    {
        if (m_InputManager == null)
            return;

	    m_InputManager.AddActionListener("MouseLeft", EActionTrigger.DOWN, PerformAttack);
    }

    override void EOnDeactivate(IEntity owner)
    {
		if (m_InputManager == null)
            return;

        m_InputManager.RemoveActionListener("MouseLeft", EActionTrigger.DOWN, PerformAttack);
    }

    void PerformAttack()
    {
        m_Player = EntityUtils.GetPlayer();
        
        if (m_Player == null)
            return;
        
		ChimeraCharacter character = ChimeraCharacter.Cast(m_Player);
		if (!character)
			return;
		
		CharacterControllerComponent controller = character.GetCharacterController();
		if (!controller)
			return;
		
		CharacterInputContext inputContext = controller.GetInputContext();

        if (inputContext == null)
            return;

        inputContext.SetMeleeAttack(true);

        return;
        
        CharacterAnimationComponent m_CharacterAnimation = CharacterAnimationComponent.Cast(m_Player.FindComponent(CharacterAnimationComponent));
        SCR_CharacterCommandHandlerComponent characterCommandHandler = SCR_CharacterCommandHandlerComponent.Cast(m_CharacterAnimation.FindComponent(SCR_CharacterCommandHandlerComponent));
        characterCommandHandler.GetCommandModifier_Melee().Attack();
        
        SCR_MeleeComponent m_MeleeComponent = SCR_MeleeComponent.Cast(m_Player.FindComponent(SCR_MeleeComponent));
        m_MeleeComponent.PerformAttack();
    }
}

/*!
\}
*/
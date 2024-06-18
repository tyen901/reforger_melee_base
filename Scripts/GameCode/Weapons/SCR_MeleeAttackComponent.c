/*!
\addtogroup Weapon
\{
*/

class SCR_MeleeAttackComponentClass: ScriptComponentClass
{
}

class SCR_MeleeAttackComponent: ScriptComponent
{
    IEntity m_Owner;
    IEntity m_Player;
    InputManager m_InputManager;
    BaseItemAnimationComponent m_AnimationComponent;

    override void OnPostInit(IEntity owner)
    {
        m_Owner = owner;
        m_InputManager = GetGame().GetInputManager();
        owner.SetFlags(EntityFlags.ACTIVE, false);
        SetEventMask(owner, EntityEvent.FRAME);
    }

    override void EOnActivate(IEntity owner)
    {
        if (m_InputManager == null)
            return;

	    m_InputManager.AddActionListener("MouseLeft", EActionTrigger.DOWN, PerformAttack);
        m_InputManager.AddActionListener("MouseRight", EActionTrigger.DOWN, BlockDown);
        m_InputManager.AddActionListener("MouseRight", EActionTrigger.UP, BlockUp);
    }

    override void EOnDeactivate(IEntity owner)
    {
		if (m_InputManager == null)
            return;

        m_InputManager.RemoveActionListener("MouseLeft", EActionTrigger.DOWN, PerformAttack);
        m_InputManager.RemoveActionListener("MouseRight", EActionTrigger.DOWN, BlockDown);
        m_InputManager.RemoveActionListener("MouseRight", EActionTrigger.UP, BlockUp);
    }

    void PerformAttack()
    {
        m_Player = EntityUtils.GetPlayer();
        
        if (!m_Player)
            return;
        
		ChimeraCharacter character = ChimeraCharacter.Cast(m_Player);
		if (!character)
			return;
		
		CharacterControllerComponent controller = character.GetCharacterController();
		if (!controller)
			return;
		
		CharacterInputContext inputContext = controller.GetInputContext();

        if (!inputContext)
            return;

        inputContext.SetMeleeAttack(true);
    }

    void BlockDown()
    {
        m_IsBlocking = true;
    }

    void BlockUp()
    {
        m_IsBlocking = false;
    }

    bool IsBlocking()
    {
        return m_IsBlocking;
    }
}

/*!
\}
*/
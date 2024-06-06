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
    IEntity m_Owner;
    IEntity m_Player;

    override void OnPostInit(IEntity owner)
    {
        m_Owner = owner;
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
}

/*!
\}
*/
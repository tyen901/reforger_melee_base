/*!
\addtogroup Weapon
\{
*/

[EntityEditorProps(category: "GameScripted/Weapon", description: "Melee animation component for the weapon.")]
class SCR_MeleeAnimationComponentClass: WeaponAnimationComponentClass
{
}

class SCR_MeleeAnimationComponent: WeaponAnimationComponent
{
    protected int m_CharacterBlockVarID = -1;
    protected int m_WeaponBlockingVarID = -1;
	
    protected IEntity m_Owner;

    protected bool m_IsBound = false;

    protected CharacterAnimationComponent m_CharacterAnimationComponent;

    void SCR_MeleeAnimationComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
    {
        m_Owner = ent;
        m_WeaponBlockingVarID = BindBoolVariable("IsBlocking");
    }

    override event protected void EOnInit(IEntity owner)
    {
        const SCR_PlayerController playerController = SCR_PlayerController.Cast(GetGame().GetPlayerController());

        if (!playerController)
            return;

        const SCR_ChimeraCharacter chimeraCharacter = SCR_ChimeraCharacter.Cast(playerController.GetControlledEntity());

        if (!chimeraCharacter)
            return;

        const SCR_CharacterControllerComponent characterController = SCR_CharacterControllerComponent.Cast(chimeraCharacter.GetCharacterController());

        if (!characterController)
            return;

        m_CharacterAnimationComponent = characterController.GetAnimationComponent();

        if (!m_CharacterAnimationComponent)
            return;

        m_CharacterBlockVarID = m_CharacterAnimationComponent.BindVariableBool("IsBlocking");
        m_IsBound = true;
    }

	override event protected bool OnPrepareAnimInput(IEntity owner, float ts)
    {
        SCR_MeleeAttackComponent meleeAttackComponent = SCR_MeleeAttackComponent.Cast(m_Owner.FindComponent(SCR_MeleeAttackComponent));

        if (!meleeAttackComponent)
            return super.OnPrepareAnimInput(owner, ts);

        if (!m_CharacterAnimationComponent)
            return super.OnPrepareAnimInput(owner, ts);

        if (m_IsBound)
        {
            bool isBlocking = meleeAttackComponent.IsBlocking();
            SetBoolVariable(m_WeaponBlockingVarID, isBlocking);
            m_CharacterAnimationComponent.SetVariableBool(m_CharacterBlockVarID, isBlocking);
        }

        return super.OnPrepareAnimInput(owner, ts);
    };
}



/*!
\}
*/
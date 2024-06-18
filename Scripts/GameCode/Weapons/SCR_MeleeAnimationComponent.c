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
    protected IEntity m_Owner;
    protected int m_WeaponBlockingVarID = -1;
	
    void SCR_MeleeAnimationComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
    {
        m_Owner = ent;
        m_WeaponBlockingVarID = BindBoolVariable("IsBlocking");
    }

	override event protected bool OnPrepareAnimInput(IEntity owner, float ts)
    {
        SCR_MeleeAttackComponent meleeAttackComponent = SCR_MeleeAttackComponent.Cast(m_Owner.FindComponent(SCR_MeleeAttackComponent));

        if (!meleeAttackComponent)
            return super.OnPrepareAnimInput(owner, ts);

        bool isBlocking = meleeAttackComponent.IsBlocking();

        SetBoolVariable(m_WeaponBlockingVarID, isBlocking);

        return super.OnPrepareAnimInput(owner, ts);
    };
}



/*!
\}
*/
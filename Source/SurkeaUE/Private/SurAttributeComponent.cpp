#include "SurAttributeComponent.h"

USurAttributeComponent::USurAttributeComponent()
{
	Health = 100;

}

bool USurAttributeComponent::ApplyHealthChange(float Delta)
{
	Health += Delta;
	// �����жϲ����Ƿ�ɹ���ɣ����ɫ������������Ƶ��������ʧ��
	// Ŀǰ�ȷ���true
	return true;
}
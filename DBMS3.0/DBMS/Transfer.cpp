#include "stdafx.h"
#include "Transfer.h"
#include "Struct.h"

Transfer::Transfer()
{
	//m_oldField = new Field[1];
}


Transfer::~Transfer()
{
}
// 保留要修改的字段信息，继而传递给dlg
//void Transfer::OldField(Field oldField)
//{
//	/*m_oldField[0].m_FieldName = oldField.m_FieldName;
//	m_oldField[0].m_FieldType = oldField.m_FieldType;
//	m_oldField[0].m_Length = oldField.m_Length;
//	m_oldField[0].m_Hint = oldField.m_Hint;
//	m_oldField[0].m_Min = oldField.m_Min;
//	m_oldField[0].m_Max = oldField.m_Max;
//	m_oldField[0].m_Default = oldField.m_Default;
//	m_oldField[0].m_Primary = oldField.m_Primary;
//	m_oldField[0].m_Null = oldField.m_Null;*/
//}
// dlg获取旧的字段，并在初始化的时候显示出来
//Field* Transfer::GetOldField()
//{
//	return m_oldField;
//}

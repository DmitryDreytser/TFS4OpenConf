
#include "UI.h"
#include "CommonFunctions.h"
#include "NameTable.h"
#include "MMS_Filter.h"
#include "Storage.h"
#include "Container.h"
#include "Strings.h"


DWORD CUIUnits::YesNo2DWORD(GCString& str)
{
	if( str.CollateNoCase("��") == 0 ) return 1;
	return 0;
}

DWORD StrToID(GCString& str)
{
	char *stopstring;
	return strtol(str, &stopstring, 16);
}

bool CUICommands::ReadFromFile(GCString& FileName)
{
	CLexer Lexer(FileName);
	if( !Lexer.IsValid() )
	{
		Msg(0, "ERR: Can not open file '%s': %s", FileName, strerror(errno));
		throw NULL;
	}

	CUICommand* Command = NULL;
	int state = 1; //1 - ���������; 2 - �������; 3 - �������; 4 ������ ����������� ����������; 5 - ����������� '}' ������
	GCString token, value;

	Msg(2, "������ ����� '%s'", FileName);

	NCommands = 0;
	Commands.SetSize(128);

	//� �������� ������ ������ ������� (��������������.��������.������� ������)
	//������� � ������ ������������ �������� ���� �� ������ (������ ":")
	while( Lexer.GetToken(token, ":") )
	{
		Lexer.SkipSpaces();
		switch( state )
		{
		case 1: //������ ��������� ������
			if( token == '{' )
				state = 2;
			else
			{
				Lexer.GetRest(value);
				if( token.CollateNoCase("���������") == 0 ) 
					StorageName = value;
				else if( token.CollateNoCase("���") == 0 )
				{
					if( value.CollateNoCase("��������") == 0 )
						IsChild = false;
					else
						IsChild = true;
				}
				else if( token.CollateNoCase("�������������") == 0 )
					InterfaceName = value;
				else if( token.CollateNoCase("��������") == 0 )
					ParentInterface = value;
				else if( token.CollateNoCase("��������") == 0 )
					Description = value;
				else if( token.CollateNoCase("���������������������") == 0 )
					NoOperMenuPresent = YesNo2DWORD(value);
				else if( token.CollateNoCase("�������������������������������������") == 0 )
					IsDefault = YesNo2DWORD(value);
			}
			break;
		case 2: //������ �������
			if( token == '}' )
			{
				state = 5;
			}
			else
			{
				Lexer.GetRest(value);
				NCommands++;
				if( Commands.GetSize() < NCommands ) Commands.SetSize(Commands.GetSize()*2);
				Command = &(Commands[NCommands-1]);
				if( IsChild )
				{
					//��� ���������� ���������� ������� �������� � ��������� 2 (�������� � state = 3 �� ����������)
					Command->Command = token;
					Command->CmdParameter = value;
					Command->FormFullCommand();
				}
				else
				{
					Command->ID = StrToID(token);
					state = 3;
				}
			}
			break;
		case 3: //������ �������
			if( token == '}' ) //����������� ������ ��� �������
			{
				state = 2;
			}
			else if( token == '{' ) //����������� ������ ��� �������
			{
			}
			else
			{
				if( token.CollateNoCase("�����1") == 0 ) 
					Lexer.GetRest(Command->Param1);
				else if( token.CollateNoCase("Hint") == 0 )
					Lexer.GetRest(Command->Hint);
				else if( token.CollateNoCase("HotKey") == 0 )
				{
					Lexer.GetToken(token, ": \t", false);
					Lexer.GetRest(value);
					if( value.IsEmpty() )
					{
						Command->HotKey = StrToID(token);
					}
					else
					{
						Command->HotKeyModifier = StrToID(token);
						Command->HotKey = StrToID(value);
					}
				}
				else if( token.CollateNoCase("�������") == 0 )
				{
					Lexer.GetRest(Command->Command);
					Command->FormFullCommand();
				}
				else if( token.CollateNoCase("��������") == 0 )
				{
					Lexer.GetRest(Command->CmdParameter);
					Command->FormFullCommand();
				}
			}
			break;
		case 4: //������ ������� ����������� ����������
			break;
		case 5: //��� ��������� �� ��� �����
			Msg(0, "WARN: ����������� ������: %s", Lexer.FilePosInfo());
			break;
		default:
			Msg(0, "WARN: ����������� ������: %s", Lexer.FilePosInfo());
			break;
		}
	}

	if( state == 5 )
		return true;
	else
		return false;
}

bool CUICommands::Write(CStorage& Storage, GCString& SrcDir)
{
	CNameTableRecord* nt_rec = NameTable.Find(NT_UICommands);
	Storage.CreateStream(nt_rec->PrepareStorageName());
	IStream* pStream = Storage.pStream;

	pStream->Write(&ID, sizeof(ID), NULL);
	if( IsChild )
	{
		WriteSizedString(pStream, ParentInterface);
	}
	else
	{
		WriteSizedString(pStream, Description);
	}
	pStream->Write(&NoOperMenuPresent, sizeof(NoOperMenuPresent), NULL);
	pStream->Write(&IsDefault, sizeof(IsDefault), NULL);

	if( IsChild )
	{
		WriteSizedString(pStream, Description);
	}
	
	pStream->Write(&NCommands, sizeof(NCommands), NULL);

	for( DWORD i = 0; i < NCommands; i++ )
	{
		CUICommand& cmd = Commands[i];
		
		cmd.CmdParameter.Replace("~~", "\n");
		if( IsChild )
		{
			WriteSizedString(pStream, cmd.Command);
			WriteSizedString(pStream, cmd.CmdParameter);
		}
		else
		{
			pStream->Write(&cmd.ID, sizeof(cmd.ID), NULL);
			
			WriteSizedString(pStream, cmd.Param1);
			WriteSizedString(pStream, cmd.Hint);
			
			pStream->Write(&cmd.HotKeyModifier, sizeof(cmd.HotKeyModifier), NULL);
			pStream->Write(&cmd.HotKey, sizeof(cmd.HotKey), NULL);

			WriteSizedString(pStream, cmd.Command);
			WriteSizedString(pStream, cmd.CmdParameter);
		}
	}

	Msg(2, "CPY: %s", nt_rec->PrepareFileName(SrcDir));

	return true;
}

//===========================================================================
CUIMenu* CUIMenu::AddItem()
{
	NItems++;
	if( Items.GetSize() < NItems )
	{
		if( Items.GetSize() == 0 )
			Items.SetSize(32);
		else
			Items.SetSize(Items.GetSize()*2);
	}

	Items[NItems-1].Parent = this;
	Items[NItems-1].Commands = Commands;
	
	return &(Items[NItems-1]);
}

bool CUIMenu::ReadFromFile(CLexer& Lexer, CUIMenu* Parent, int level)
{
	Level = level;
	NItems = 0;
	CUIMenu* Item;
	GCString token, value;
	while( Lexer.GetToken(token, ": \t") )
	{
		if( token == '{' )
		{
		}
		else if( token == '}' )
		{
			return true;
		}
		else if( token.CollateNoCase("�������") == 0 )
		{
			Item = AddItem();
			Item->Type = MenuItem;
			Lexer.GetRest(Item->Caption);
			Item->Level = Level + 1;
			//Command ID on next line
			Lexer.GetLine(token);
			Item->ID = Commands->CommandName2ID(token);
			if( Item->ID == 0 )
			{
				Msg(0, "WARN: ���� '%s' ��������� �� �������������� ������", Item->Caption);
				Item->ID = 0x0000CFFE;
			}
			Lexer.GetRest(token);
		}
		else if( token.CollateNoCase("�����������") == 0 )
		{
			Type = MainMenu;
			ID = 0x01;
		}
		else if( token.CollateNoCase("�������") == 0 )
		{
			Item = AddItem();
			Item->Type = MenuGroup;
			Item->ID = 0xFFFFFFFF;
			Lexer.GetRest(Item->Caption);
			Item->ReadFromFile(Lexer, Item, level + 1);
		}
		else if( token.CollateNoCase("�����������") == 0 )
		{
			Item = AddItem();
			Item->Type = MenuDividor;
			Item->ID = 0x00;
			Item->Level = Level + 1;
		}
	}
	return true;
}


bool CUIMenu::ReadFromFile(GCString& FileName)
{
	CLexer Lexer(FileName);

	Msg(2, "������ ����� '%s'", FileName);

	ReadFromFile(Lexer, NULL, 0);
	return true;
}

bool CUIMenu::Write(CStorage& Storage, GCString& SrcDir)
{
	if( Type == MainMenu )
	{
		CNameTableRecord* nt_rec = NameTable.Find(NT_UIMenu);
		Storage.CreateStream(nt_rec->PrepareStorageName());
		Msg(2, "CPY: %s", nt_rec->PrepareFileName(SrcDir));
	}
	IStream* pStream = Storage.pStream;

	pStream->Write(&ID, sizeof(ID), NULL);

	if( Type == MenuGroup || Type == MenuItem )
	{
		WriteSizedString(pStream, Caption);
	}

	if( Type == MainMenu || Type == MenuGroup )
	{
		pStream->Write(&NItems, sizeof(NItems), NULL);
	}

	for( int i = 0; i < NItems; i++ )
	{
		Items[i].Write(Storage, SrcDir);
	}

	return true;
}


bool CUIPanel::Write(CStorage& Storage)
{
	IStream* pStream = Storage.pStream;
	WriteSizedString(pStream, Caption);
	pStream->Write(&NButtons, sizeof(NButtons), NULL);
	pStream->Write(&Placement, sizeof(Placement), NULL);
	pStream->Write(&IsVisible, sizeof(IsVisible), NULL);
	pStream->Write(&OnNewLine, sizeof(OnNewLine), NULL);
	return true;
}

void CUIPanels::SetButtonCommand(CUIButton& Button, GCString& id, GCString& FileName)
{
	Button.ID = Commands->CommandName2ID(id);
	if( Button.ID == 0 && id != MenuDividorString )
	{
		Msg(0, "WARN: ������ �� ������ '%s' ��������� �� �������������� ������", FileName);
		Button.ID = 0xCFFE;
	}
}

bool CUIPanels::ReadFromFile(GCString& FileName)
{
	CLexer Lexer(FileName);
	GCString token, value;
	CUIPanel Panel;
	CUIButton Button;
	char *divs_normal = ": \t", *divs_button = "", *dividors = divs_normal;
	int state = 0; //0 - ��� �������; 1 - ������ ������; 2 - ������ ������ ������ ������; 3 - ������ �������� ������; 4 - ������ ������ � ����������

	Msg(2, "������ ����� '%s'", FileName);

	while( Lexer.GetToken(token, dividors) )
	{
		if( token == '{' ) 
			continue;
		if( token == '}' )
		{
			state = 0;
			dividors = divs_normal;
			continue;
		}

		Lexer.GetRest(value);
		switch( state )
		{
		case 0:
			if( token.CollateNoCase("������") == 0 )
			{
				Panels.Add(Panel);
				Panels[NPanels].Caption = value;
				NPanels++;
				state = 1;
			}
			else if( token.CollateNoCase("������") == 0 )
			{
				state = 2;
			}
			else if( token.CollateNoCase("���������������") == 0 )
			{
				state = 3;
			}
			else if( token.CollateNoCase("��������������������") == 0 )
			{
				state = 4;
			}
			break;
		case 1:
			{
				CUIPanel& Panel = Panels[NPanels-1];
				if( token.CollateNoCase("������������") == 0 )
				{
					if( value.CollateNoCase("������") == 0 ) Panel.Placement = 0xE81B;
					if( value.CollateNoCase("�����")  == 0 ) Panel.Placement = 0xE81C;
					if( value.CollateNoCase("������") == 0 ) Panel.Placement = 0xE81D;
					if( value.CollateNoCase("�����")  == 0 ) Panel.Placement = 0xE81E;
				}
				else if( token.CollateNoCase("���������") == 0 )
					Panel.IsVisible = YesNo2DWORD(value);
				else if( token.CollateNoCase("������������") == 0 )
					Panel.OnNewLine = YesNo2DWORD(value);
				else if( token.CollateNoCase("������") == 0 )
					Panel.NButtons = atol(value);
			}
			break;
		case 2:
			AllButtons.Add(Button);
			SetButtonCommand(AllButtons[NButtons], token, FileName);
			NButtons++;
			break;
		case 3:
			TextButtons.Add(Button);
			SetButtonCommand(TextButtons[NTextButtons], token, FileName);
			Lexer.GetToken(token, dividors);
			TextButtons[NTextButtons].Caption = token;
			NTextButtons++;
			break;
		case 4:
			PictureButtons.Add(Button);
			SetButtonCommand(PictureButtons[NPictureButtons], token, FileName);
			NPictureButtons++;
			break;
		}

		if( state == 2 || state == 3 || state == 4 )
			dividors = divs_button;
		else
			dividors = divs_normal;
	}

	return true;
}

bool CUIPanels::Write(CStorage& Storage, GCString& Dir)
{
	CNameTableRecord* nt_rec = NameTable.Find(NT_UIPanels);
	Storage.CreateStream(nt_rec->PrepareStorageName());
	IStream* pStream = Storage.pStream;
	DWORD i;

	pStream->Write(&ID, sizeof(ID), NULL);
	pStream->Write(&NPanels, sizeof(NPanels), NULL);
	
	for( i = 0; i < NPanels; i++ )
	{
		Panels[i].Write(Storage);
	}

	for( i = 0; i < NButtons; i++ )
	{
		pStream->Write(&AllButtons[i].ID, sizeof(AllButtons[i].ID), NULL);
	}

	pStream->Write(&NTextButtons, sizeof(NTextButtons), NULL);
	for( i = 0; i < NTextButtons; i++ )
	{
		WriteSizedString(pStream, TextButtons[i].Caption);
		pStream->Write(&TextButtons[i].ID, sizeof(TextButtons[i].ID), NULL);
	}

	pStream->Write(&NPictureButtons, sizeof(NPictureButtons), NULL);
	for( i = 0; i < NPictureButtons; i++ )
	{
		pStream->Write(&PictureButtons[i].ID, sizeof(PictureButtons[i].ID), NULL);
	}

	CNameTableRecord* nt_rec_b = NameTable.Find(NT_UIPanelsBMP);
	Storage.AppendFile(pStream, nt_rec_b->PrepareFileName(Dir));

	Msg(2, "CPY: %s", nt_rec->PrepareFileName(Dir));
	Msg(2, "CPY: %s", nt_rec_b->PrepareFileName(Dir));

	return true;
}

void CUserInterfaces::ReadFromDir(GCString& SrcDir, CUserInterface* Parent)
{
	CObjectOrdering Ordering(3);

	if( !Ordering.OpenFile(SrcDir) )
		return;

	while( Ordering.ReadString() )
	{
		GCString DirName;
		DirName.Format("%s\\%s", SrcDir, Ordering.GetValue(0));
		CUserInterface* Interface = new CUserInterface;
		if( Interface->ReadFromDir(DirName, Parent) )
		{
			Add(Interface);
		}
		else
		{
			delete Interface;
		}
	}
}


bool CUserInterface::ReadFromDir(GCString& SrcDir, CUserInterface* Parent)
{
	CNameTableRecord* nt_rec_c = NameTable.Find(NT_UICommands);
	CNameTableRecord* nt_rec_m = NameTable.Find(NT_UIMenu);
	CNameTableRecord* nt_rec_p = NameTable.Find(NT_UIPanels);
	CNameTableRecord* nt_rec_pb = NameTable.Find(NT_UIPanelsBMP);

	GCString CommandsFName = nt_rec_c->PrepareFileName(SrcDir);
	GCString MenuFName = nt_rec_m->PrepareFileName(SrcDir);
	GCString PanelsFName = nt_rec_p->PrepareFileName(SrcDir);

	if( !FileExist(CommandsFName) ) return false;

	this->DirName = SrcDir;
	this->Parent = Parent;
	Commands.ReadFromFile(CommandsFName);
	Name = Commands.InterfaceName;

	if( FileExist(MenuFName) ) Menu.ReadFromFile(MenuFName);
	if( FileExist(PanelsFName) ) Panels.ReadFromFile(PanelsFName);

	Children.ReadFromDir(SrcDir, this);

	return true;
}

bool CUserInterface::Write(CStorage& Storage)
{
	Storage.Create(Commands.StorageName);
	Commands.Write(Storage, DirName);
	if( !Commands.IsChild )
	{
		Menu.Write(Storage, DirName);
		Panels.Write(Storage, DirName);
	}
	CContainer CC;
	CC.Create(Storage, false, CT_UserInterfaces);
	Storage.Close();

	for( int i = 0; i < Children.GetSize(); i++ )
	{
		Children[i]->Write(Storage);
	}

	return true;
}

void CUserInterface::MakeContainerContents(GCString& CC)
{
	if( Commands.IsChild )
		CC += ",{\"SubUsersInterfaceType\",\"";
	else
		CC += ",{\"UsersInterfaceType\",\"";
	CC += Commands.StorageName;
	CC += "\",\"";
	CC += Name;
	CC += "\",\"\"}";

	for( int i = 0; i < Children.GetSize(); i++ )
	{
		Children[i]->MakeContainerContents(CC);
	}
}


bool CompileUI(CStorage& Storage, GCString& SrcDir)
{
	CNameTableRecord* nt_rec = NameTable.Find(NT_UserInterface);
	GCString UIDir = nt_rec->PrepareDirName(SrcDir);
	CStorage UIStorage(Storage);
	CUserInterfaces UserInterfaces;

	MMS_Filter.Down();
	bool ToExtract = MMS_Filter.Test(NULL, nt_rec);
	if( ToExtract )
	{
		Msg(1, "INF: ���������������� ����������");
		UserInterfaces.ReadFromDir(UIDir);

		UIStorage.Create(nt_rec->PrepareStorageName());
		GCString CC = "{\"Container.Contents\"";
		int i, sz = UserInterfaces.GetSize();
		for( i = 0; i < sz; i++ )
		{
			CUserInterface& Interface = *(UserInterfaces.GetAt(i));
			Interface.Write(UIStorage);
			Interface.MakeContainerContents(CC);
		}
		CC += "}\n";

		UIStorage.StreamFromString(GCString("Container.Contents"), CC);
	}
	MMS_Filter.Up();
	return ToExtract;
}
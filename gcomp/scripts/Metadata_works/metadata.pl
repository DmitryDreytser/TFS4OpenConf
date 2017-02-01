
# 
# ������, ��������������� ������ � MetadataWorks.pm, � �� ���������������� �������� ��� ������� ����������� �������
# 

use locale;
use Getopt::Long;
use File::Find; #package ��� ������������ ������ ���������
use MetadataWorks;

$usage = <<EOF
�������������:
   perl Metadata.pl [���������]
��������� ����� ����:
   -d <dir>  - ������� � ����������� �������������. �� ��������� - ������� �������.
EOF
;

#default values
$root_dir = ".";
GetOptions("dir|d=s" => \$root_dir) or die Metadata::wintodos($usage);

$FldText = <<EOF
		GUID: 
		{
			�����������: ""
			�������: ""
			��� ��������: ��
			��� ������: ��
			���: ������
			�����: 33
			��������: 0
			���������� ���: 
			���������������: ���
			��������� ������: ���
			�������������: ���
			��������� ������� �����������: ���
			������ ��������� �������: ��
			����������: ��
			�����: ��
		}
EOF
;


$TableFldText = <<EOF
		�����: 
		{
			�����������: ""
			�������: ""
			���: �����
			�����: 19
			��������: 2
			���������� ���: 
			���������������: ���
			��������� ������: ��
			���� �� �������: ��
		}
EOF
;

AddRefFields(); #��������� ���� �� ��� �����������
ChangeRefFields(); #������ �������� ���� �� ���� ������������
AddDocHeadFields(); #��������� ���� � ����� ����������
AddDocTableFields(); #��������� ���� � �� ����������
ChangeDocTableFields(); # ������ �������� ����� ��������� ����� ����������




###################################################################################################################
sub AddRefFields
{
	Metadata::Start($root_dir);
	File::Find::find(\&_AddRefField, $root_dir);
	Metadata::Stop();
}

sub _AddRefField
{
	my $dir = $File::Find::dir;
	my $fname = $_;
	return unless $fname =~ m/^(.*)(\.mdp)$/i; #��� ����� ������ ����� � ����������� mdp
	return unless $dir =~ m/[\/\\]�����������[\/\\]/i;

	my $obj_name = Metadata::GetObjectName($dir);
	if( Metadata::AddRefField($fname, "����������.$obj_name.GUID", $FldText) > 0 )
	{
		print Metadata::wintodos("Add GUID to $obj_name\n");
	}	
}	

#------------------------------------------------------------------------------------------------------
sub ChangeRefFields
{
	Metadata::Start($root_dir);
	File::Find::find(\&_ChangeRefField, $root_dir);
	Metadata::Stop();
}

sub _ChangeRefField
{
	my $dir = $File::Find::dir;
	my $fname = $_;
	return unless $fname =~ m/^(.*)(\.mdp)$/i; #��� ����� ������ ����� � ����������� mdp
	return unless $dir =~ m/[\/\\]�����������[\/\\]/i;

	if( Metadata::SetFieldAttr($fname, "GUID", "�����", "40") > 0 )
	{
		my $obj_name = Metadata::GetObjectName($dir);
		print Metadata::wintodos("$obj_name Changed\n");
	}	
}	

#------------------------------------------------------------------------------------------------------
sub AddDocHeadFields
{
	Metadata::Start($root_dir);
	File::Find::find(\&_AddDocHeadField, $root_dir);
	Metadata::Stop();
}	

sub _AddDocHeadField
{
	my $dir = $File::Find::dir;
	my $fname = $_;
	return unless $fname =~ m/^(.*)(\.mdp)$/i; #��� ����� ������ ����� � ����������� mdp
	return unless $dir =~ m/[\/\\]���������[\/\\]/i;

	my $obj_name = Metadata::GetObjectName($dir);
	if( Metadata::AddDocHeadField($fname, "��������.$obj_name.GUID", $FldText) > 0 )
	{
		print Metadata::wintodos("Add GUID to head $obj_name\n");
	}	
}

#------------------------------------------------------------------------------------------------------
sub AddDocTableFields
{
	Metadata::Start($root_dir);
	File::Find::find(\&_AddDocTableField, $root_dir);
	Metadata::Stop();
}	

sub _AddDocTableField
{
	my $dir = $File::Find::dir;
	my $fname = $_;
	return unless $fname =~ m/^(.*)(\.mdp)$/i; #��� ����� ������ ����� � ����������� mdp
	return unless $dir =~ m/[\/\\]���������[\/\\]/i;

	my $obj_name = Metadata::GetObjectName($dir);
	if( Metadata::AddDocTableField($fname, "��������.$obj_name.�����", $TableFldText) > 0 )
	{
		print Metadata::wintodos("Add ����� to table $obj_name\n");
	}	
}
#------------------------------------------------------------------------------------------------------


#------------------------------------------------------------------------------------------------------
sub ChangeDocTableFields
{
	Metadata::Start($root_dir);
	File::Find::find(\&_ChangeDocTableFields, $root_dir);
	Metadata::Stop();
}

sub _ChangeDocTableFields
{
	my $dir = $File::Find::dir;
	my $fname = $_;
	return unless $fname =~ m/^(.*)(\.mdp)$/i; #��� ����� ������ ����� � ����������� mdp
	return unless $dir =~ m/[\/\\]���������[\/\\]/i;

	if( Metadata::SetFieldAttr($fname, "�����", "���� �� �������", "��") > 0 )
	{
		my $obj_name = Metadata::GetObjectName($dir);
		print Metadata::wintodos("$obj_name Changed\n");
	}	
}	
#------------------------------------------------------------------------------------------------------



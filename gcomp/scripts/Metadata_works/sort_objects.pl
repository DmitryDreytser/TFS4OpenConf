
use locale;
use Getopt::Long;
use MetadataWorks;

$usage = <<EOF
�������������:
   perl sort_objects.pl [���������]
��������� ����� ����:
   -d <dir>  - ������� � ����������� �������������. �� ��������� - ������� �������.
   -n - ���������� �� �������� ���������������
   -t - ���������� �� ��������� ��������������� (�� ���������)
EOF
;

#default values
my $root_dir = ".";
my $numeric = 0;
my $textual = 0;
GetOptions("dir|d=s" => \$root_dir, "numeric|n" => \$numeric, "textual|text|t" => \$textual ) or die Metadata::wintodos($usage);

Metadata::Start($root_dir);

if( $textual )
{
	Metadata::SortObjectsByTextualIDs();
}
elsif( $numeric )
{
	Metadata::SortObjectsByNumericIDs();
}
else
{
	die Metadata::wintodos("�� ������ ������ ���������� (����� -n ��� -t)\n");
}

Metadata::Stop();
	  


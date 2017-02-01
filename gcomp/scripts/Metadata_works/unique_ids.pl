
use locale;
use Getopt::Long;
use MetadataWorks;

$usage = <<EOF
�������������:
   perl unique_ids.pl [���������]
��������� ����� ����:
   -d <dir>  - ������� � ����������� �������������. �� ��������� - ������� �������.
EOF
;

#default values
$root_dir = ".";
GetOptions("dir|d=s" => \$root_dir) or die Metadata::wintodos($usage);

Metadata::Start($root_dir);

if( Metadata::MakeIDsUnique() > 0 )
{
	Metadata::Stop();
}
	  
exit(Metadata::CheckTextIDs());

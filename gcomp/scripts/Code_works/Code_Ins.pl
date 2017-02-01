#!/usr/bin/perl

#==============================================================================================================
# ������ ��� �������� ������� ���� � ������.
#
#==============================================================================================================
#����� - ����� ������� mailto:adirks@ngs.ru
#
#��� ��������� �������� ��������� ����������� ������������. �� ������
#�������������� � (���) �������������� �� �� �������� GNU Generic Public License.
#
#������ ��������� ���������������� � �������� ��������� ��������, ��
#��� �����-���� ��������, � ��� ����� ��� �������� ����������� ��� ������� ���
#�����-���� ������ ������������ �����.
#
#� ������ ������� �������� �� ���������� ����� ����� ������������ �� ������
#http://www.gnu.org/licenses/gpl.txt ��� � �����
#gnugpl.eng.txt
#
#� ������� ��������� �������� ����� ������������ �� ������
#http://gnu.org.ru/gpl.html ��� � �����
#gnugpl.rus.txt
#
#�� ������ �������� ����� GNU Generic Public License ������ � ������ ���� ���������.
#���� ��� �� ��� - �������� �� ���� ������� (mailto:adirks@ngs.ru , mailto:fe@alterplast.ru) ��� ��������
#Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA

use locale;
use File::Find; #package ��� ������������ ������ ���������
use CodeWorks;

use strict "vars";
use vars qw/ $usage
	$root_dir $pattern_dir $backups $quiet $real_quiet /;

$usage = <<EOF
�������������:
   perl code_works.pl [���������]
��������� ����� ����:
   -h        - ���� �����
   -d <dir>  - �������, ������ ������� ����� ������� (*.1s). �� ��������� ����� ���������� �
               �������� ��������.
   -p <dir>  - ������� � ��������� ����. �� ��������� - �������.
   -b        - ����� ����������� ����� �������� ������� (� ����������� .1s~)
   -q        - ����� �����
   -qq       - ������ ����� �����
EOF
;

#default values
$root_dir = ".";
$pattern_dir = ".";
$backups = 0;
$quiet = 0;
$real_quiet = 0;

#command line processing
use Getopt::Long;
GetOptions(
	"dir|d=s" => \$root_dir,
	"patterns|p=s" => \$pattern_dir,
	"backup|b" => \$backups,
	"q" => \$quiet,
	"qq" => \$real_quiet
	) 
	or die CodeWorks::wintodos($usage);
$quiet = 1 if $real_quiet;

use Cwd;
$root_dir = Cwd::abs_path($root_dir);
$pattern_dir = Cwd::abs_path($pattern_dir);
#traverse through dirs and do work
File::Find::find(\&ProcessMod, $root_dir);


sub ProcessMod()
{
	my $dir = $File::Find::dir;
	my $fname = $_; #File::Find ���������� � $_ ��� �������� �����
	return unless $fname =~ m/^(.*)(\.1s)$/i; #��� ����� ������ ����� � ����������� 1s

	my ($type, $ObjName, $ModuleType) = CodeWorks::GetObjectName($dir . "/" . $fname);
	my $pattern_fname = "$pattern_dir/$ModuleType.pl";
	
	if( not -f $pattern_fname )
	{
		$quiet or print CodeWorks::wintodos("$dir/$fname: ��� ������� ($pattern_fname)\n");
		return;
	}
	
	#load change rules
	open CODE, "<$pattern_fname";
	my $code = join("", (<CODE>));
	close CODE;

	CodeWorks::LoadModule($fname); #load module
	my $text = join("\n", @CodeWorks::lines);
	eval $code; #apply changes
	CodeWorks::PrintErrors();
	
	my $new_text = join("\n", @CodeWorks::lines);
	$text ne $new_text or return; #������ �� �������� - �� ����� � � ���� ������
	
	#save changes
	open NEW_MODULE, "> $fname";
    print NEW_MODULE $new_text;
   	close NEW_MODULE;

	$real_quiet or print CodeWorks::wintodos("$dir/$fname: ������ ($pattern_fname)\n");
}

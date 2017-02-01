#$ENGINE PerlScript
#$NAME CodeBeautifier
#��� ������������� ������� � OpenConf ���������������� ��� ���������� �������


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

use vars qw/ $InOpenConf /;
$InOpenConf = 1 if( defined $Configurator);

use strict "vars"; #�������� ������������ ������������� ����������
use locale;
use POSIX qw(locale_h);
use Getopt::Long;
use File::Find; #package ��� ������������ ������ ���������

#������� ���������� ����������
use vars qw/ $tab_size
	$blank_after_proc $blank_before_endproc $blank_after_endproc $procname_after_endproc
	$blank_after_if $blank_before_elseif $blank_before_endif
	$blank_after_while $blank_before_wend
	$space_around_ops /;
use vars qw/ $pat_comment $pat_proc $pat_endproc /;
use vars qw/ $file_name $root_dir $keep_old_files /;
use vars qw/ $line $line_number $trimmed_line $state @states $level /;
use vars qw/ $proc_name $proc_start /;
use vars qw/ $in_string $skip_blanks $blank_lines $unended_operator/;
use vars qw/ $FormattedText /;

############################################################################
##       ��������� �������������� ����      ################################
$tab_size = 4;
$blank_after_proc = 0;      #������ ������ � ������ ���������/�������
$blank_before_endproc = 0;  #������ ������ � ����� ���������/�������
$blank_after_endproc = 1;   #������ ������ ����� ���������/�������
$procname_after_endproc = 30;#��� ������ � ������������ ����� ����������  (��������  �������������� //�����������)
                            #�������� ���� ���������� - ��� ���������� �����, ����� �������� ����� ��������� 
                            #"�������", � ����� ��������� �����������. ���� ������ ������ ������ ����������, �� 
                            #����������� ���������
                            #������������� �������� - ����������� ��������� ��� ����
$blank_after_if = 0;        #������ ������ � ������ ����� '����'
$blank_before_elseif = 0;   #������ ������ ����� '�����', '���������'
$blank_before_endif = 0;    #������ ������ ����� '���������'
$blank_after_while = 0;     #������ ������ � ������ ������ '����' � '���'
$blank_before_wend = 0;     #������ ������ � ����� ������ '����' � '���'
$space_around_ops = 1;      #������� ����� ���������� � ����� �������
############################################################################

$pat_comment = "\/\/.*"; #EOL comment pattern
$pat_proc = "�������|Function|���������|Procedure";
$pat_endproc = "������������|EndFunction|��������������|EndProcedure";

my $usage = <<EOF
�������������:
   perl code_beautifier.pl [���������]
��������� ����� ����:
   -h|--help  - ���� �����
   -d|--dir <dir>  - �������, ������ ������� ����� ����������� ������� ��� �������������� (*.1S).
       �� ��������� ����� ���������� � �������� ��������.
   -f|--file <file>  - ��� �����, ������� ����� ���������������. ���� ����� � ������� � ��� �����,
       �� �������������� ����� ������ ����.
   -k|--keep  - ��������� �������� ������ ����������, ��������� ������������ � ����� *.new.1S
EOF
;

$root_dir = '.';

#################################################################################
#################################################################################
main();  #��� ������������� ��� OpenConf ������ ��� ������� ���� ����������������
#################################################################################
#################################################################################


sub main
{
	return if( $InOpenConf );
	
	die wintodos($usage) unless GetOptions("dir|d=s" => \$root_dir, "file|f=s" => \$file_name, "keep|k" => \$keep_old_files);

	if( $file_name )
	{
		$File::Find::name = $file_name;
		$_ = $file_name;
		BeautifyModule();
	}
	else
	{
		find(\&BeautifyModule, $root_dir);
	}
}

sub Beautify_OpenConf
{
	my $Text = shift;
	my @Lines = split(/\r\n/, $Text, -1);
	_BeautifyModule(@Lines);
	#Message("'$FormattedText'");
	$FormattedText =~ s/\n/\r\n/g;
	return $FormattedText;
}

sub perror
{
	if( $InOpenConf )
	{
		Message(shift, 1);
	}
	else
	{
		print STDERR wintodos(shift), "\n";
	}
}


sub _BeautifyModule
{
	my @Lines = @_;
	$line_number = 0;
	my $NLines = @_;

	$FormattedText = "";
	$state = "module";
	$level = 0;
	pop @states while (scalar @states) > 0;
	$skip_blanks = 0;
	$blank_lines = 0;
	$in_string = 0;
	$unended_operator = 0;
	my $module_head = 1;

	foreach $line (@Lines)
	{
		$line_number++;
		$line =~ s/[\r\n]//g; #����� ����������� \n � \r, ���� ��� ��� ����
		$trimmed_line = $line;
		$trimmed_line =~ s/^\s*(.*?)\s*$/$1/;
		#print "$state, $level, $skip_blanks (blanks = $blank_lines), unended = $unended_operator : '$trimmed_line'\n";

		if( not $trimmed_line )
		{
			$blank_lines++ if not $skip_blanks;
			next;
		}

		if( $InOpenConf ) { Status("$line_number / $NLines"); }	

		my $keyword_match = 0;
		
		if( $state eq "module" )
		{
			$keyword_match = 1 if check_proc_begin() or check_if() or check_cycle() or check_try();
			if( $keyword_match and $module_head )
			{
				$FormattedText .= "\n" if $blank_lines;
				$module_head = 0;
			}	
		}
		elsif( $state eq "proc" )
		{
			$keyword_match = 1 if check_end_proc() or check_if() or check_cycle() or check_try() or check_proc_begin();
		}
		elsif( $state eq "if_multiline" )
		{
			check_multiline_if();
			$keyword_match = 1;
		}
		elsif( $state eq "if" )
		{
			$keyword_match = 1 if check_if() or check_cycle() or check_elsif() or check_endif() or check_try() or check_proc_begin();
		}
		elsif( $state eq "try" )
		{
			$keyword_match = 1 if check_try() or check_if() or check_cycle();
		}
		elsif( $state eq "cycle" )
		{
			$keyword_match = 1 if check_cycle() or check_endcycle() or check_if() or check_try() or check_proc_begin();
		}

		if( $keyword_match )
		{
			#$blank_lines = 0;
			$unended_operator = 0;
			next;
		}

		$unended_operator = 0 if $in_string and $unended_operator == 0;

		#Message("$line: $state  $skip_blanks  $blank_lines");
		$FormattedText .= "\n" if $blank_lines;
		$blank_lines = 0;
		if( $unended_operator )
			{ print_line( offset(1), format_expr($trimmed_line) ); }
		else
			{ print_line( format_expr($trimmed_line) ); }
		$skip_blanks = 0;

		if( not $in_string )
		{
			if( $trimmed_line =~ m/^.*;(\s*$pat_comment)*$/ )
				{$unended_operator = 0;}
			elsif( $trimmed_line =~ m/^$pat_comment$/ )
				{$unended_operator = 0;}
			else
				{$unended_operator++;}
		}
	}

	if( $InOpenConf ) { Status(""); }	
	return $FormattedText;
}

sub BeautifyModule
{
	my $FName = $_; #File::Find ���������� � $_ ��� �������� �����
	if( $file_name )
	{
		$FName = $file_name;
	}
	else
	{
		return unless $FName =~ m/^(.*)(\.1S)$/i; #��� ����� ������ ����� � ����������� 1S
		return if $FName =~ m/^(.*)(\.new\.1S)$/i; #��� �� ����� ����� � ����������� new.1S
	}
	$FName =~ m/^(.*)(\.\S*)$/i;
	my $newFName = "$1.new$2";

	perror($File::Find::name);
	open IN, "< $FName";
	open OUT, "> $newFName";

	print OUT _BeautifyModule((<IN>));

	close OUT;
	close IN;
	if( not $keep_old_files )
	{
		if( !rename($newFName, $FName) )
		{
			print wintodos("Can't move $newFName to $FName: $!\n");
		}
	}
}

sub format_op_spaces
{
	my $lspace = shift;
	my $op = shift;
	my $rspace = shift;

	return ("", "") if not $space_around_ops;
	$lspace = " " if not $lspace and $op ne ",";
	$rspace = " " if not $rspace;
	return ($lspace, $rspace);
}

sub format_expr
{
	my $expr = shift;
	my $formatted = "";
	my $lspace = "";
	my $rspace = "";
	my $op = "";

	if( $expr =~ m/^(\s+)(.*)$/ )
	{
		$formatted = $1;
		$expr = $2;
	}
	#$expr =~ s/^((.*?)("[^"]*")*)(\s*$pat_comment)*$/$1/;
	#my $eol_comment = $2;
	my $eol_comment = '';

	while( length($expr) > 0 )
	{
		if( $in_string )
		{
			my $c = substr($expr, 0, 1);
			if( $c eq '"' )
			{
				if( substr($expr, 1, 1) eq '"' )
				{
					$formatted .= '"';
					$expr = substr($expr, 1);
				}
				else
				{
					$in_string = 0;
				}
			}
			$formatted .= $c;
			$expr = substr($expr, 1);
		}
		elsif( substr($expr, 0, 1) eq '"' )
		{
			$formatted .= $lspace . '"';
			$expr = substr($expr, 1);
			$in_string = 1;
		}
		elsif( substr($expr, 0, 1) eq '/' and substr($expr, 1, 1) eq '/') #EOL comment
		{
			$eol_comment = $expr;
			$expr = '';
		}
		elsif( $expr =~ m/^\s*;(.*)$/i ) #ending  ';'
		{
			$expr = $1;
			$formatted .= ";";
			($lspace, $rspace) = ("", "");
		}	
		elsif( $expr =~ m/^(=|\(|\+|Return|�������)(\s*)-\s*(.*)$/i ) #unary minus
		{
			$op = $1;
			$rspace = $2;
			$expr = $3;
			($lspace, $rspace) = format_op_spaces($lspace, $op, $rspace);
			#Message("'$lspace'  '$op'  '$rspace'     '$expr'");
			$formatted .= $lspace . $op . $rspace . "-";

			($lspace, $rspace) = ("", "");
		}	
		elsif( $expr =~ m/^(<>|<=|>=|,|=|\+|-|\*|\/|%|<|>)(\s*)(.*)$/i )
		{
			$op = $1;
			$rspace = $2;
			$expr = $3;

			($lspace, $rspace) = format_op_spaces($lspace, $op, $rspace);
			$rspace = "" if $op eq "," and substr($expr, 0, 1) eq ","; #2 ������� ������ - ��� �������

			$formatted .= $lspace . $op . $rspace;

			($lspace, $rspace) = ("", "");
		}
		elsif( $expr =~ m/^(\)\s*)(�|AND|���|OR)(\s*\()(.*)$/i )
		{
			$op = uc($2);
			$lspace = substr($1, 1);
			$rspace = substr($3, 0, length($3) - 1);
			($lspace, $rspace) = format_op_spaces($lspace , $op, $rspace);

			$formatted .= ")" . $lspace . $op . $rspace . "(";
			$expr = $4;

			$lspace = "";
			$rspace = "";
		}
		elsif( not $formatted and $expr =~ m/^(�|AND|���|OR)(\s*\()(.*)$/i )
		{
			$op = uc($1);
			$rspace = substr($2, 0, length($2) - 1);
			($lspace, $rspace) = format_op_spaces($lspace , $op, $rspace);

			$formatted .= $op . $rspace . "(";
			$expr = $3;

			$lspace = "";
			$rspace = "";
		}
		elsif( $expr =~ m/^(\)\s*)(�|AND|���|OR)$/i )
		{
			$op = uc($2);
			$lspace = substr($1, 1);
			$rspace = "";
			($lspace, $rspace) = format_op_spaces($lspace , $op, $rspace);

			$formatted .= ")" . $lspace . $op;
			$expr = "";

			$lspace = "";
			$rspace = "";
		}
		elsif( $expr =~ m/^(\s+)(.*)$/ )
		{
			$rspace = $1;
			$expr = $2;
		}
		else
		{
			$formatted .= $lspace;
			$formatted .= substr($expr, 0, 1);
			$expr = substr($expr, 1);
			$rspace = "";
		}

		$lspace = $rspace;
	}
	$formatted .= $rspace;
	$formatted .= $eol_comment;

	return $formatted;
}

sub check_proc_begin
{
	if( $trimmed_line =~ m/^($pat_proc)(\s+(\S+)\(.*\)\s*)(�������|Export)*(.*)($pat_endproc)(\s*)($pat_comment)*$/i )
	{
		perror("    �������������� ������ � ��������� '$proc_name'") if $level > 0;
		$proc_name = "";
		$proc_start = 0;
		print_line(ucfirst($1), format_expr($2), ucfirst($4), $5, ucfirst($6), $7, $8);
		$level = 0;
		$unended_operator = 0;
		return 1;
	}
	elsif( $trimmed_line =~ m/^($pat_proc)(\s+)(\S+)(\s*\(.*\))((\s+(�������|Export|�����|Forward))*)(;*)(\s*$pat_comment)*$/i )
	{
		perror("    �������������� ������ � ��������� '$proc_name'") if $level > 0;
		$proc_name = $3;
		$proc_start = $line_number;
		$level = 0;
		print_line(ucfirst($1), $2, $3, format_expr($4), ucfirst($5), $8, $9);
		if( not $5 =~ m/�����|Forward/i )
		{
			push @states, $state;
			$state = "proc";
			$level = 1;
			$FormattedText .= "\n" if $blank_after_proc;
		}
		else
		{
			$FormattedText .= "\n" if $blank_after_endproc;
		}
		$skip_blanks = 1;
		$blank_lines = 0;
		$unended_operator = 0;
		return 1;
	}
	return 0;
}

sub check_end_proc
{
	if( $trimmed_line =~ m/^($pat_endproc)([^\/\s]*)((?:\s*$pat_comment)*)$/i )
	{
		$FormattedText .= "\n" if $blank_before_endproc;

		perror("    �������������� ������ � ��������� '$proc_name'") if $level != 1;
		$level = 0;
		my ($endproc, $text_after, $comment) = ($1, $2, $3);
		
		if( $procname_after_endproc >= 0 )
		{
			my $proc_lines = $line_number - $proc_start + 1;
			my $need_comment = $proc_lines >= $procname_after_endproc;
			if( !$need_comment and !$text_after and ($comment =~ m/^\s*\/\/\s*($proc_name)?\s*\(?\s*\)?\s*$/i) )
			{
				print_line(ucfirst($endproc));
			}
			elsif( $need_comment and !$text_after and ($comment =~ m/^\s*$/) )
			{
				print_line(ucfirst($endproc), " //$proc_name()");
			}
			else
			{
				print_line(ucfirst($endproc), format_expr($text_after), $comment);
			}
		}
		else
		{
			print_line(ucfirst($endproc), format_expr($text_after), $comment);
		}
		
		$state = pop @states;
		$proc_name = "";
		$proc_start = 0;
		$FormattedText .= "\n" if $blank_after_endproc;
		$skip_blanks = 1;
		$blank_lines = 0;
		return 1;
		$unended_operator = 0;
	}
	return 0;
}

sub check_if
{
	if( $trimmed_line =~ m/^(����|If)([(\s].*[)\s])(�����|Then)(\s.*)(���������|EndIf)(;*.*?)(\s*$pat_comment)*$/i ) #���� if � ���� �������
	{
		$FormattedText .= "\n" if $blank_lines;
		print_line(ucfirst($1), format_expr($2), ucfirst($3), format_expr($4), ucfirst($5), format_expr($6), $7);
	}
	elsif( $trimmed_line =~ m/^(����|If)([(\s].*[)\s])(�����|Then)(\s*[\s;].*?){0,1}(\s*$pat_comment)*$/i )
	{
		$FormattedText .= "\n" if $blank_lines;
		print_line(ucfirst($1), format_expr($2), ucfirst($3), format_expr($4), $5);
		push @states, $state;
		$state = "if";
		$level++;
		$skip_blanks = 1;
		$blank_lines = 0;
		$FormattedText .= "\n" if $blank_after_if;
	}
	elsif( $trimmed_line =~ m/^(����|If)([(\s].*)$/i ) #then �� ������ ������
	{
		$FormattedText .= "\n" if $blank_lines;
		print_line(ucfirst($1), format_expr($2));
		push @states, $state;
		push @states, "if";
		$state = "if_multiline";
		$skip_blanks = 1;
		$blank_lines = 0;
	}
	else
	{
		return 0;
	}

	$unended_operator = 0;
	return 1;
}

sub check_multiline_if
{
	if( $trimmed_line =~ m/^$pat_comment$/i )
	{
		$FormattedText .= offset($level + 1) . " " . $trimmed_line . "\n";
	}
	elsif( $trimmed_line =~ m/^(.*[)\s])(�����|Then)(\s*$pat_comment)*$/i )
	{
		$state = pop @states;
		$FormattedText .= offset($level + 1) . " " . format_expr($1) . "\n" if $1;
		$FormattedText .= offset($level) . ucfirst($2) . "\n" if $2;
		$level++;
	}
	elsif( $trimmed_line =~ m/^(�����|Then)(\s*$pat_comment)*$/i )
	{
		$state = pop @states;
		$FormattedText .= offset($level) . ucfirst($1) . $2 . "\n";
		$level++;
	}
	else
	{
		$FormattedText .= offset($level + 1) . " " . format_expr($trimmed_line) . "\n";
	}
	$skip_blanks = 1;
}

sub check_elsif
{
	if( $trimmed_line =~ m/^(�����|Else)(\s.*?){0,1}(\s*$pat_comment)*$/i )
	{
		$level--;
		$FormattedText .= "\n" if $blank_before_elseif;
		print_line(ucfirst($1), format_expr($2), $3);
	}
	elsif( $trimmed_line =~ m/^(���������|ElsIf)([(\s].*[)\s])(�����|Then)(\s.*?){0,1}(\s*$pat_comment)*$/i )
	{
		$level--;
		$FormattedText .= "\n" if $blank_before_elseif;
		print_line(ucfirst($1), format_expr($2), ucfirst($3), format_expr($4), ucfirst($5), $6, $7);
	}
	elsif( $trimmed_line =~ m/^(���������|ElsIf)([(\s].*)$/i ) #then �� ������ ������
	{
		$level--;
		$FormattedText .= "\n" if $blank_before_elseif;
		print_line(ucfirst($1), format_expr($2));
		
		push @states, $state;
		$level--;
		$state = "if_multiline";
	}
	else
	{
		return 0;
	}

	$level++;
	$skip_blanks = 1;
	$blank_lines = 0;

	return 1;
}


sub check_endif
{
	if( $trimmed_line =~ m/^(���������|EndIf)(;*.*?)($pat_comment)*$/i )
	{
		$level--;
		$FormattedText .= "\n" if $blank_before_endif;
		print_line(ucfirst($1), format_expr($2), $3);
		$state = pop @states;
		$skip_blanks = 0;
		$blank_lines = 0;
		return 1;
	}
	return 0;
}

sub check_cycle
{
	if( $trimmed_line =~ m/^(���|For)(\s.*\s)(��|To)(\s.*\s)(����|Do)(\s*$pat_comment)*$/i )
	{
		$FormattedText .= "\n" if $blank_lines;
		print_line(ucfirst($1), format_expr($2), ucfirst($3), format_expr($4), ucfirst($5), $6);
	}
	elsif( $trimmed_line =~ m/^(����|While)([\s("']*.*?[\s)"'])(����|Do)(\s*$pat_comment)*$/i )
	{
		$FormattedText .= "\n" if $blank_lines;
		print_line(ucfirst($1), format_expr($2), ucfirst($3), $4);
	}
	else
	{
		return 0;
	}

	$level++;
	push @states, $state;
	$state = "cycle";
	$skip_blanks = 1;
	$blank_lines = 0;
	$FormattedText .= "\n" if $blank_after_while;
	return 1;
}

sub check_endcycle
{
	if( $trimmed_line =~ m/^(����������|EndDo)(;*.*?)(\s*$pat_comment)*$/i )
	{
		$state = pop @states;
		$level--;
		$FormattedText .= "\n" if $blank_before_wend;
		print_line(ucfirst($1), format_expr($2), $3);
		$blank_lines = 0;
		return 1;
	}
	return 0;
}


sub	check_try
{
	if( $trimmed_line =~ m/^(�������|Try)(\s*$pat_comment)*$/i )
	{
		$FormattedText .= "\n" if $blank_lines;
		print_line(ucfirst($1), $2);
		$level++;
		push @states, $state;
		$state = "try";
		$skip_blanks = 1;
		$blank_lines = 0;
		return 1;
	}
	elsif( $trimmed_line =~ m/^(����������|Except)(\s*$pat_comment)*$/i )
	{
		$level--;
		print_line(ucfirst($1), $2);
		$level++;
		$skip_blanks = 1;
		$blank_lines = 0;
		return 1;
	}
	elsif( $trimmed_line =~ m/^(������������|EndTry)(;*.*?)(\s*$pat_comment)*$/i )
	{
		$state = pop @states;
		$level--;
		print_line(ucfirst($1), format_expr($2), $3);
		$blank_lines = 0;
		$skip_blanks = 0;
		return 1;
	}
	elsif( $trimmed_line =~ m/^(����������|Except)\s+(������������|EndTry)(;*.*?)(\s*$pat_comment)*$/i )
	{
		$state = pop @states;
		$level--;
		print_line(ucfirst($1), " ", ucfirst($2), format_expr($3), $4);
		$blank_lines = 0;
		$skip_blanks = 0;
		return 1;
	}
	return 0;
}

##################################################################
sub offset
{
	my $i = shift;
	my $offset = "";
	$offset .= "\t" while $i-- > 0;
	return $offset;
}

sub print_line
{
	$FormattedText .= offset($level);
	foreach (@_)
	{
		$FormattedText .= $_;
	}	
	$FormattedText .= "\n";
}

 sub wintodos {
	my $win_chars = "\xA8\xB8\xB9\xC0\xC1\xC2\xC3\xC4\xC5\xC6\xC7\xC8\xC9\xCA\xCB\xCC\xCD\xCE\xCF\xD0\xD1\xD2\xD3\xD4\xD5\xD6\xD7\xD8\xD9\xDA\xDB\xDC\xDD\xDE\xDF\xE0\xE1\xE2\xE3\xE4\xE5\xE6\xE7\xE8\xE9\xEA\xEB\xEC\xED\xEE\xEF\xF0\xF1\xF2\xF3\xF4\xF5\xF6\xF7\xF8\xF9\xFA\xFB\xFC\xFD\xFE\xFF";
	my $dos_chars = "\xF0\xF1\xFC\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8A\x8B\x8C\x8D\x8E\x8F\x90\x91\x92\x93\x94\x95\x96\x97\x98\x99\x9A\x9B\x9C\x9D\x9E\x9F\xA0\xA1\xA2\xA3\xA4\xA5\xA6\xA7\xA8\xA9\xAA\xAB\xAC\xAD\xAE\xAF\xE0\xE1\xE2\xE3\xE4\xE5\xE6\xE7\xE8\xE9\xEA\xEB\xEC\xED\xEE\xEF";
	$_ = shift;
	return $_ if $^O eq "cygwin";
	eval("tr/$win_chars/$dos_chars/");
	return $_;
}

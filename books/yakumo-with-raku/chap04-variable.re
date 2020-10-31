= 変数

@<B>{藍}: まずはプログラミング言語の基本的な機能である変数、そしてRakuの基本データ型を見ていこう。
Rakuのデータ型はかなりPerl5と近いけれど、 クラスの概念や静的型の概念が導入されているから面白いよ。


== Rakuのデータ型とシジル

RakuはPerlの影響が強く、変数は@<strong>{シジル(sigil)+変数名}で表現します。
シジルとはその変数がどのようなデータ構造なのかを端的に示した記号です。

Rakuは4種類のシジルがあります。

//table[raku_sigil_table][Rakuのシジル]{
シジル	役割
@<code>{$}	スカラ変数
@<code>{@}	配列
@<code>{%}	ハッシュ
@<code>{&}	コード変数(サブルーチン)
//}

それぞれのシジルに対応したデータ型の前に、まず変数の定義方法について見ていきます。

== my : レキシカル変数の宣言

Rakuでは変数宣言に@<kw>{宣言子,declarator}を利用します。
一般的な変数であるレキシカル変数の宣言には@<b>{my}をを使います。 
レキシカル変数とは、Perl5とRakuではローカル変数のことを指します。 @<fn>{my_perl5_note}

Perl5と同様に宣言したい変数名の前にmyを記述します。

//listnum[my_example_1][myでの変数宣言の例][perl6]{
my $hoge = "hello";
my $number = 34;
//}

//footnote[my_perl5_note][Perl5の歴史的背景でローカル変数とは呼ばず、 レキシカル変数と呼びます]

== constant : 定数の宣言

Rakuでは定数の宣言に@<kw>{constant}を使います。
constantは変数宣言と変数の代入を同時に行う必要があります。 

//listnum[const_example_1][constantでの宣言][perl6]{
> constant $const_var = "hello";
hello
//}

定数の呼び出しは通常の変数と同様です。

//listnum[const_example_11][constantでの宣言した定数の呼び出し][perl6]{
> say $const_var;
hello
//}

再代入を行おうとした場合、 例外が発生します。

//listnum[const_example_12][constantでの宣言した定数への再代入][perl6]{
> $const_var = "world!";
Cannot assign to an immutable value
  in block <unit> at <unknown file> line 1
//}

これはコンパイルタイムではなく、 実行時に例外が出ます。
試しにスクリプトを実行してみます。
//listnum[const_example_123][constantでの宣言した定数への再代入][perl6]{
constant $msg = "hello";
$msg.say;

$msg = "world!";
$msg.say;
//}

//terminal[const_Example_1234][実行結果]{
$ raku const_test.p6
hello
Cannot assign to an immutable value
  in block <unit> at const_test.p6 line 4
//}

最初の@<code>{$msg.say}までは実行されているため、 @<code>{hello}が出力されています。
しかし4行目の@<code>{ $msg = "world!"}でエラーが発生しており、 メッセージが出力されているのがわかります。

初期宣言時に代入を忘れた場合、コンパイルエラーになります。

//listnum[const_example_2][constantで代入を忘れた場合][perl6]{
say "hello";
constant $msg;

$msg = "hello";
$msg.say;
//}


//terminal[const_example_21][実行結果]{
$ raku forget_const_example.p6
===SORRY!=== Error while compiling /Users/anatofuz/forget_const_example.p6
Missing initializer on constant declaration
at /Users/anatofuz/forget_const_example.p6:2
------> constant $msg⏏;
//}

@<code>{===SORRY!===}から始まるメッセージが出力されました。 実際にはこのSORRYを囲っている@<code>{=}は赤色になっており、いかにもな雰囲気が出ています。
Rakuにおいてこのメッセージは、基本的にコンパイルタイムでのエラーです。

== スカラー変数

@<code>{$}から始まる変数のことを@<strong>{スカラー変数}といいます。
スカラーとは「単一」のような意味の単語であり、 その名前の通り値を1つのみ持つことが出来ます。
スカラー変数はデフォルトでは型が無いように振る舞うため、 一度文字列を代入した変数に再度数値を代入することも可能です。

スカラー変数を出力したい場合は@<strong>{say}メソッドを利用します。
sayはスカラー変数にインスタンスメソッドとして提供されているので、 @<code>{$scalar.say}とすることも可能です。
sayはサブルーチンとしても利用することが可能ですので、@<code>{say "$scalar"}と引数を与えた関数として使うことも可能です。


Rakuでは変数の中身を利用する場合は@<strong>{""}で文字列を囲みます。

試しに変数宣言、出力、代入を行ってみましょう。

//listnum[scalar_Example1][スカラー変数の代入と使用][perl6]{
my $ran = "八雲 藍";
my $chen = "橙";
my $yukari_age = 10000;


$ran.say;

say "$chen は猫です";

say "yukari age is $yukari_age";

$yukari_age = "unmeasurable";

say "yukari age is $yukari_age";
//}

//terminal[scalar_Example1][実行結果]{
$ raku scalar_example1.raku
八雲 藍
橙 は猫です
yukari age is 10000
yukari age is unmeasurable
//}

また@<code>{.say}のようなインスタンスメソッドの一覧は @<code>{$scalar.^methods}で確認可能です。

//terminal[scalar_Example1_repl][replで確認]{
> my $scalar = "hello";
hello
> $scalar.^methods;
(BUILD Capture Int Num Version chomp pred succ match subst-mutate parse-base samecase samemark samespace word-by-word trim-leading trim-trailing trim WORDS_AUTODEREF encode NFC NFD NFKC NFKD unival univals wordcase trans parse-names uniparse indent codes chars uc lc tc fc tclc flip ord WHY WHICH Bool Str Stringy DUMP ACCEPTS chop starts-with ends-with substr-eq contains indices index rindex Numeric gist raku comb subst ords lines split words substr substr-rw BUILDALL)
//}


== 配列

@<code>{@}から始まる変数は配列です。
1つの配列は複数の値やスカラー変数から成り立っています。

配列の宣言はスカラー変数と同様にmyで行います。
初期化したい場合は右辺に値のリストを書きます。

//listnum[array_ex1][配列の宣言|代入][perl6]{
my @yakumo_family = ('yukari', 'ran', 'chen');
my @fairy = 'tiruno', 'daiyousei';
my @chaos = 1, "nyaaa";
//}

Rakuではリストを作る際などで丸括弧を省略することが可能です。
また、文字列からなるリストを作る際、 @<code>{<>}演算子(@<code>{qw//}でも可能)を使うと、クォーテーションを省略可能です。
この場合はスペース区切りで1単語として扱われます。

//listnum[array_ex2][配列の宣言|代入][perl6]{
my @yakumo_family = <yukari ran chen>;
//}


=== []演算子を使った要素の参照

配列の中の要素を参照する場合のやり方はいくつかあります。
基本的なやり方として@<code>{[]}演算子を利用して、インデックスを指定して値を取得することが出来ます。

//listnum[array_ex3_term][配列の要素のアクセス][perl6]{
my @yakumo_family = <yukari ran chen>;
say '@yakumo_family[0]:' ~ "@yakumo_family[0]";
say '@yakumo_family[1]:' ~ "@yakumo_family[1]";
say '@yakumo_family[2]:' ~ "@yakumo_family[2]";
say '@yakumo_family[*-1]:' ~ "@yakumo_family[*-1]";
//}


//terminal[array_ex3_term][配列の要素のアクセス]{
$ raku array_ex3.raku
@yakumo_family[0]:yukari
@yakumo_family[1]:ran
@yakumo_family[2]:chen
@yakumo_family[*-1]:chen
//}

上記の例では@<code>{~}が出てきましたが、これは文字列結合の演算子です。
@<code>{[]}の中にインデックスの値を入れると取り出すことが可能です。
配列の最後の値を取り出したい場合は、@<code>{*-1}を利用することで取得可能です。


=== 値の追加

配列に値を追加するやり方の一つに、前述した@<code>{[]}演算子を使うものがあります。
もっとも、他のプログラミング言語でプログラミングをしている方にはおなじみかと思います。

現在の配列のサイズより大きいインデックスを指定して代入した場合、動的にそのインデックスまで配列が拡張されます。
拡張された分には、Any型が代入されます。 @<fn>{any_array_ex1_c04}

//terminal[alloc_array_test1][配列に値を追加する]{
> my @aList = ();
[]
> @aList[10] = "hello";
hello
> @aList
[(Any) (Any) (Any) (Any) (Any) (Any) (Any) (Any) (Any) (Any) hello]
//}

代入された@<code>{(Any)}は真偽値として評価した場合は偽の値となります。

//terminal[alloc_array_test2][真偽値で評価してみる]{
> my @aList = ();
[]
> @aList[9] = "a";
a
> if @aList[0] { say "true!!" } else { say "false!!" }
false!!
//}


//footnote[any_array_ex1_c04][Any型はRakuの大体のオブジェクトの基底クラスです]

=== 多次元配列

Rakuでは多次元配列を持つことが可能です。各要素で次元を区切る時には@<code>{;}を使います。
REPLで実際に入力しながら確認していきます。

//terminal[multi_array_test1][多次元配列]{
> my @chara2spell = ();
[]
> @chara2spell[0;0] = "reimu";
reimu
> @chara2spell[0;1] = "musou_huuin";
musou_huuin
> @chara2spell[0;2] = "houmajin";
houmajin
> @chara2spell[1] = ["marisa", "master_spark", "Bracing_star"];
[marisa master_spark Bracing_star]
> say @chara2spell[0;0]
reimu
> say @chara2spell[0]
[reimu musou_huuin houmajin]
> say @chara2spell[0;2]
houmajin
> say @chara2spell;
[[reimu musou_huuin houmajin] [marisa master_spark Bracing_star]]
//}

この例では各配列の要素が3つの要素持つ配列となっています。
配列への代入は、一つひとつ要素を指定して行うやり方(@<code>{reimu}(0番目)の場合)と、まとめて代入するやり方(@<code>{marisa}(1番目))があります。

=== 固定長配列

配列の宣言時に要素数をつけることで固定長配列を作ることが可能です。
配列の各要素はAnyで初期化されます。
確保していない領域に代入やアクセスをするとエラーが発生します。

//terminal[array_concreate_ex][固定長配列]{
> my @aList[3]; #要素数3で宣言
[(Any) (Any) (Any)]
> @aList[2] = "hello"; #確保済みの範囲なら自由に使える
hello
> @aList[3] = "hello"; #index外のものにアクセスするとエラー
Index 3 for dimension 1 out of range (must be 0..2)
  in block <unit> at <unknown file> line 1
//}


=== push

pushは配列の最後に要素を追加します。

//listnum[array_ex5][push][perl6]{
my @koumakyo = <rumia daiyousei ⑨ meirin koakuma>;

say @koumakyo;

@koumakyo.push("Patchouli");

say @koumakyo;

@koumakyo.push: "sakuya";

say @koumakyo;
//}

//terminal[array_ex5_term][実行結果]{
$ raku array_ex5.raku
[rumia daiyousei ⑨ meirin koakuma]
[rumia daiyousei ⑨ meirin koakuma Patchouli]
[rumia daiyousei ⑨ meirin koakuma Patchouli sakuya]
//}

3回目のpushでは@<code>{: "str"}と@<code>{:}を使っています。
Rakuではpushに限らずメソッドの@<code>{()}を省略し、@<code>{:}で代用することが可能です。

=== unshift

unshiftはpushの逆で、先頭に要素を追加します。

//listnum[array_ex6][unshift][perl6]{
my @koumakyo = <daiyousei ⑨ meirin koakuma Patchouli sakuya>;

say @koumakyo;

@koumakyo.unshift("rumia");

say @koumakyo;

//}

//terminal[array_ex5_term][実行結果]{
$ raku unshift_test.raku
[daiyousei ⑨ meirin koakuma Patchouli sakuya]
[rumia daiyousei ⑨ meirin koakuma Patchouli sakuya]
//}

=== pop 

@<code>{pop}は配列の終端から値を取り出します。
破壊的なメソッドですので、配列は最後の値が取り除かれた状態になります。

//listnum[array_pop][pop][perl6]{
my @yakumo = <yukari ran chen>;

say  @yakumo.pop;
say pop @yakumo;
say pop @yakumo;

say @yakumo;
//}


//terminal[array_pop][実行結果]{
chen
ran
yukari
[]
//}

=== shift

@<code>{shift}は@<code>{pop}の逆に対応します。先頭から値を取り出します。

//listnum[array_shift][shift][perl6]{
my @yakumo = <yukari ran chen>;

say  @yakumo.shift;
say shift @yakumo;
say shift @yakumo;

say @yakumo;
//}

//terminal[array_shift][実行結果]{
$ raku array_ex_shift.raku
yukari
ran
chen
[]
//}

=== first

firstメソッドは配列の先頭から特定の条件を初めて満たす値を返します。
条件を指定しない場合は配列の0番目を返します。

条件には様々なオプションをつけることが可能です。

 * @<code>{:end}
 ** 条件を満たす最後の値が帰ります。
 * @<code>{:k}
 ** マッチした値のインデックスが帰ります
 * @<code>{:kv}
 ** マッチしたインデックスと値がリスト形式で帰ってきます
 * @<code>{:p}
 ** マッチしたインデックスと値がPairクラスのインスタンス(ほとんどハッシュと同じ)で帰ってきます

実際に今回は1から100までの整数のリストを作り、firstで検証してみます。

//listnum[array_ex4_term][firstメソッド][perl6]{
my @numbers = (1..100);
say @numbers.first;
say @numbers.first: * > 50; # 50以上の数
say @numbers.first: * %3 == 0, :end; #3で割り切れる数の最後の数
say @numbers.first: * %3 == 0, :k;   #3で割り切れる最初の数のインデックス
say @numbers.first: * %3 == 0, :kv;  #3で割り切れる最初の数のインデックスと値のリスト
say @numbers.first: * %3 == 0, :p;   #3で割り切れる最初の数のインデックスと値のペア
//}

//terminal[array_ex3_term][配列の要素のアクセス]{
$ raku array_ex4.raku
1
51
99
2
(2 3)
2 => 3
//}

@<code>{:kv}で指定した場合はリストが帰ってきており、 @<code>{:p}で指定した場合はハッシュの形式で帰ってきていることが確認出来ます。

=== end

endは配列の最後のインデックスを返します。

//terminal[array_end_term][endでインデックスを取得する]{
> my @hakurei = <reimu aun clown>;
[reimu aun clown]
> @hakurei.end;
2
//}


=== head

headは配列の先頭の要素を出力します。shiftとは違い非破壊的なメソッドです。
headを@<code>{()}を付けずに呼び出した場合、先頭の文字列が返ってきます。

@<code>{()}の中には数値を引数として設定可能です。
配列の0番目が先頭から1番目なので、0番目にアクセスしたい場合は@<code>{.head(1)}と書きます。
先頭から2つ値を取りたい場合は@<code>{.head(2)}などと書きます。
注意したいのは@<code>{()}をつけた上で数値を入れてしまうと、返り値の型が文字列Strではなく、 Seqとして返ってきます。
この返り値を@<code>{$}シジルで受け取ってしまうと意図せぬ挙動を招く可能性があるので、@<code>{()}を使った呼び出しの場合は配列で受け取りましょう。

//listnum[array_ex_head][headメソッド][perl6]{
my @koumakyo = <rumia daiyousei 9 meirin koakuma Patchouli sakuya remilia fandre>;

my $rumia = @koumakyo.head;  #()を書かない
my $rumia_not_arguments = @koumakyo.head(); #()の中に引数をいれない

say $rumia;
say $rumia_not_arguments;
say $rumia_not_arguments.^name;

my @one-two-boss = @koumakyo.head(2); 
#引数を指定して配列で受け取る

say @one-two-boss;
say @one-two-boss.^name;


my $rumia_miss = @koumakyo.head(1);
#引数を指定してスカラで受け取る

say $rumia_miss;
say $rumia_miss.^name;
//}


//terminal[head_term][headの実行結果]{
$ raku array_ex_head.raku
rumia
rumia
Str
[rumia daiyousei]
Array
(rumia)
Seq
//}


=== tail

tailはheadの逆...つまり配列の最後の要素にアクセスすることができるメソッドです。
tailもheadと同様に@<code>{.tail}のみ、または@<code>{.tail()}で呼び出した場合は最後の要素の文字列が返ります。
引数として後ろから数えて何個要素を取得するか、整数値を取ることが出来ます。

//terminal[array_tail][tailの実行結果]{
> my @koumakyo = <rumia daiyousei 9 meirin koakuma Patchouli sakuya remilia fandre>;
[rumia daiyousei 9 meirin koakuma Patchouli sakuya remilia fandre]
> @koumakyo.tail  #()を付けない場合は文字列
fandre
> @koumakyo.tail() #上と同様
fandre
> @koumakyo.tail(1) #(1)でもリストが返る
(fandre)
> @koumakyo.tail(2) #後ろから2つの要素を取得
(remilia fandre)

//}

=== elems

elemsは配列の要素数を出力します。
なお遅延評価の配列ではエラーが帰ってきます。

//terminal[array_elems][elemsの実行結果]{
> my @foo = <a b c d e f g>;
[a b c d e f g]
> @foo.elems;
7
> my @hoge = (1..*);
[...]
> @hoge.elems;
Cannot .elems a lazy list
  in block <unit> at <unknown file> line 1
//}


=== splice

spliceは配列の中の特定のデータを削除・置き換えることができるメソッドです。

まずは削除だけの例を見てみましょう。
spliceで削除する場合@<code>{.splice(削除を開始する要素のインデックス, 削除する個数)}という形で呼び出します。
例えば(a,b,c,d,e)のbとcを消したい場合は @<code>{.splice(1,2)}の様に指定します。
メソッドの返り値は消した要素のリストとなっています。

実際にプログラムを書いて検証してみます。

//listnum[array_ex_splice][spliceメソッドで削除する][perl6]{
my @koumakyo = <rumia daiyousei 9 meirin koakuma Patchouli sakuya remilia fandre>;

my @removes = @koumakyo.splice(3,5); #meirin, koakuma, Patchouli, sakuya, remiliaの5人を削除

say '@koumakyo:' ~ @koumakyo;
say '@removes:' ~ @removes;
//}

//terminal[ar_splice_example_1][実行結果]{
$ raku ar_splice_ex1.raku
@koumakyo:rumia daiyousei 9 fandre
@removes:meirin koakuma Patchouli sakuya remilia
//}


3引数目に、消した値の部分に差し込みたいものを与えることが可能です。
これはリスト形式でも大丈夫です。

//listnum[array_ex_splice2][spliceメソッドで削除し、置き換える][perl6]{
my @koumakyo = <rumia daiyousei 9 meirin koakuma Patchouli sakuya remilia fandre>;

my @removes = @koumakyo.splice(3,5,(<reimu marisa aya nitori>)); 
#meirin, koakuma, Patchouli, sakuya, remiliaの5人を削除
#消した部分にreimu, marisa, aya, nitoriを差し込む

say '@koumakyo:' ~ @koumakyo;
say '@removes:' ~ @removes;
//}


//terminal[ar_splice_example_2][実行結果]{
@koumakyo:rumia daiyousei 9 reimu marisa aya nitori fandre
@removes:meirin koakuma Patchouli sakuya remilia
//}


reimu, marisa, aya, nitoriが消された部分の差し込まれているのがわかります。

=== append

appendは配列とリストを2つ以上受け取り、第一引数の配列に残りのリストを追加していくメソッドです。
pushとは異なり、appendで配列を追加する場合、追加したいリストの中身はすべて展開されてフラットなデータ構造になった上で追加されます。

//terminal[append_exam1][appendで追加してみる]{
> my @hakurei = <reimu yukari>;
[reimu yukari]
> my @hakurei = <reimu aun clown>;
[reimu aun clown]
> my @moriya = <suwako kanako sanae>;
[suwako kanako sanae]
> @hakurei.append(@moriya);
[reimu aun clown suwako kanako sanae]
> @hakurei[3]
suwako
//}

反面pushの場合はフラットにならず、単一のスカラー値として追加されるため、部分的に多次元配列になります。

//terminal[append_exam2][pushで追加してみる]{
> my @hakurei = <reimu yukari>;
[reimu yukari]
> my @hakurei = <reimu aun clown>;
[reimu aun clown]
> my @moriya = <suwako kanako sanae>;
[suwako kanako sanae]
> @hakurei.push(@moriya);
[reimu aun clown [suwako kanako sanae]]
> @hakurei[3]
[suwako kanako sanae]
//}

@<code>{@hakurei[3]}がappendで追加した場合はsuwakoだったのに対し、 pushで追加した場合は@<code>{@moriya}の配列自体になっています。

== ハッシュ

ハッシュは他の言語では連想配列、辞書型、 mapなどと呼ばれている、キーと値の組からなるデータ構造です。
Rakuでは@<strong>{%シジル}の変数はハッシュになります。

=== 宣言/ 代入

ハッシュを代入する際は、右辺値をリストにします。
リストの中身は(キー, 値)の順でハッシュに変換されます。

今回はキーを文字列でハッシュを作成します。

//terminal[hash_ex1][ハッシュの宣言と代入]{
> my %testHash = 'ran', 'kyuubi', 'nitori', 'kappa';
{nitori => kappa, ran => kyuubi}
//}

代入するリストの要素数が偶数で無い場合、キーと値のペアが作れないためエラーが発生します。

//terminal[hash_ex1_1][要素数が足りない状況での代入]{
> my %myHash = 'ran', 'yakumo', 'nitori';
Odd number of elements found where hash initializer expected:
Found 3 (implicit) elements:
Last element seen: "nitori"
  in block <unit> at <unknown file> line 1
//}

より直感的な方法として、@<code>{=>}演算子を使うやり方があります。@<fn>{info_hash_ex2}
この場合は@<code>{=>}の左側の値はクォーテーションを省略することが可能です。

//terminal[hash_ex2][ハッシュの宣言と代入]{
> my %testHash = ran => 'kyuubi', nitori =>  'kappa';
{nitori => kappa, ran => kyuubi}
//}


//footnote[info_hash_ex2][この演算子は厳密にはPairクラスのコンストラクタです]

=== 値の取得

ハッシュから値を取得するには@<code>{{"key"\}}の様にして取り出します。
キーを文字列にした場合、 直接文字を書く場合はクォーテーションで囲む必要があります。


//terminal[hash_ex3][ハッシュからvalueの取得]{
> my %testHash = ran => 'kyuubi', nitori =>  'kappa';
{nitori => kappa, ran => kyuubi}
> say %testHash{'ran'};
kyuubi
//}

クォーテーションを書くのがめんどくさい場合は、@<code>{<>}演算子@<fn>{info_hash_ex3}を使うことで回避出来ます。

//terminal[hash_ex4][<>を利用したハッシュからvalueの取得]{
> %testHash<ran>
kyuubi
//}


=== 値の削除

Hashの値の削除はキーと値の療法を削除する必要があります。
これは@<kw>{後置接周辞,postcircumfix}の@<code>{{\}}演算子に名前付き変数@<code>{:delete}を渡すことで可能です。
@<code>{{\}}演算子は、先程から利用しているハッシュのキーを指定して値を取る際に利用している@<code>{{\}}です。
そのため、値の取得を行う書き方の最後に@<code>{:delete}と付け加えると削除されます。

@<code>{delete}自体は削除したvalueを返します。

//terminal[hash_ex5][キーと値の削除]{
> my %testHash = ran => 'kyuubi', nitori =>  'kappa';
{nitori => kappa, ran => kyuubi}
> my $deleted = %testHash{'ran'}:delete;
kyuubi
> say $deleted;
kyuubi
> %testHash
{nitori => kappa}
//}


//footnote[info_hash_ex3][実際には{}にコンパイルタイムに切り替わるシンタックスシュガーです]


=== keys , values

keysはキーの一覧を、 valuesは値の一覧をそれぞれ返すメソッドです。
返り値の型はSeqで返ります。
そのため、配列として使用したい場合は@<code>{@}シジルの変数で受け取りましょう。

//terminal[hash_ex6][keys, values]{
> my %testHash = ran => 'kyuubi', nitori =>  'kappa';
{nitori => kappa, ran => kyuubi}
> %testHash.keys;
(ran nitori)
> %testHash.values;
(kyuubi kappa)
> my @names = %testHash.keys; #配列で受け取る
[nitori ran]
> @names[1].say
ran
//}


=== {}演算子の:k, :v

deleteと同様に@<code>{{\}}演算子に@<code>{:k},@<code>{:v}オプションを渡すことで同様のことが再現できます。
このときに@<code>{{\}}の中に何も文字列を入れない場合、表示はkeys, valuesと等価になります。

//terminal[hash_ex7][keys, valuesを{}演算子を使って取得する]{
> my %testHash = ran => 'kyuubi', nitori =>  'kappa';
{nitori => kappa, ran => kyuubi}
> %testHash{}:k
(nitori ran)
> %testHash{}:v
(kappa kyuubi)
//}


=== push/append

== 添字いろいろ

もう少し添え字について追求してみましょう。
配列やハッシュでは@<code>{[]}と@<code>{{\}}を利用することで各要素にアクセスすることが出来ました。

=== 添字のRole

Rakuではこれら演算子は、それぞれ特定のRole@<fn>{role_interface_index}を実装することで、ビルトイン型で無いオブジェクトに対しても設定することが可能です。
//table[raku_index_list_1][Rakuの演算子の種類]{
記号	引数	Roleの名前	具体例
@<code>{[]}	0から始まる数値		Positional	Array, List
@<code>{{\}}	文字列かオブジェクト	Associvative	Hash,Bag
//}

例えば配列のアクセスである@<code>{[]}を使うためには、 Positional Roleを実装する必要があります。
Positional Roleはrakudo上では次の様に定義されています。

//listnum[positional_role_1][Positional.pm6][perl6]{
my role Positional[::T = Mu] {
    method of() { T }

# These methods must be implemented by any object performing the Positional
# role.  The reason this is not actually activated, is that there are some
# chicken-and-egg issues with building the core if we do.
#    method elems()       { ... }
#    method AT-POS($)     { ... }
#    method EXISTS-POS($) { ... }
}
//}

例えばListの実装であるList.pm6や、Rangeクラスの実装Range.pm6では上記のRoleが実装されています。
Rakuの基本データ型であるこれらの定義は、ところどころ下位言語のNQPを使って直接VMの命令を実行しているところがあるため、 解読はなかなか大変ですが、興味がある方は読んでみましょう。

RakuではListやRange, Hashの様に@<code>{[]}と@<code>{{\}}を使ってアクセスできるようにすることを@<kw>{添字付け, subscripting}や@<kw>{インデックス付け, indexing}などと呼びます。

//footnote[role_interface_index][RakuでInterfaceに相当するものです]


=== zenスライス

Rakuでは添字演算子の中に値を入力しなかった場合、 コンパイルエラーではなく配列やハッシュなどのすべての要素が取得できます。

この手法を添字に何も入れなくてもすべてが出てくる事から、日本語の禅になぞらえて、@<strong>{zenスライス}などと呼びます。
zenスライスは文字列の中で配列やハッシュの要素を展開したい場合に利用します。

//listnum[zen_slice_ex2][zenスライスを使った文字列展開][perl6]{
my @title = ('Embodiment of Scarlet Devil', 'Perfect Cherry Blossom');
say '@title= ' ~ "@title";
say '@title[]= ' ~ "@title[]";
//}

//terminal[zen_slice_ex23][実行結果]{
@title= @title
@title[]= Embodiment of Scarlet Devil Perfect Cherry Blossom
//}

上の例では @<code>{@title}を文字列の中に書いた場合は、 特に配列が展開されることは無く、 配列名が表示されています。
zenスライスを利用して@<code>{@titile[]}と文字列中に書いた場合は、配列が展開されているのがわかります。

== シジル無し変数

@<hd>{Rakuのデータ型とシジル}で確認しましたが、 Rakuにはシジルと呼ばれる記号が必ず変数名に付きます。
実はそれ意外にも、 Rakuには@<kw>{シジル無し変数,Sigilless variables}と呼ばれるものがあります。
シジル無し変数には定義時に@<code>{\\}を変数名の前に付けます。

//listnum[sigilless_variable][シジル無し変数][perl6]{
my \chiruno = "チルノ";
say chiruno;

my \八雲 = "yakumo";
say "{八雲}藍";
//}

//terminal[sigilless_variable_output][実行結果]{
$ raku sigiless.raku
チルノ
yakumo藍
//}

シジル無し変数にはアスキー文字意外にもUTFの文字なら使用することが可能です。
文字列中で変数であることを示したい場合は@<code>{{\}}で囲む必要があります。

すでに登録されている代表的なシジル無し変数として@<code>{π}があります。

//listnum[pi][πを出力してみる][perl6]{
say π;
//}

//terminal[pi_output][πの出力]{
3.141592653589793
//}

== 代入のコンテキスト

さて改めてRakuの代入について確認をします。
例えばRakuでスカラ変数を初期値@<code>{hello}で宣言する場合は以下のような書式でした。

//list[][]{
my $string_variable = "hello";
//}

また、配列の初期化はこのように書きました。

//list[][]{
my @aArray1  = (1,2,3);
my @aArray2  = <one two three>;
//}

実はこの配列の代入文の左辺をスカラ変数にしても、Rakuでは問題なく実行が出来ます。

//terminal[assign_scalar][スカラ変数にリストを代入する]{
> my $scalar_var = (1,2,3);
(1 2 3)
> say $scalar_var;
(1 2 3)
//}

これらの振る舞いは、Rakuの代入が2種類に分けられることに起因します。
Rakuには、@<kw>{単一代入, item assignment}と、@<kw>{リスト代入, list assignment}の2種類の代入が存在します。
どちらが実行されるかは左辺のコンテキストによって決定します。
言い換えれば、 左辺がスカラ変数であるならば単一代入、それ意外ならリスト代入が実行されます。


=== 単一代入 (item assignment)

単一代入は左辺値がスカラ変数である時の代入です。
試しに右辺に文字列を複数並べて代入した場合の値と型を確認します。

//list[item_ass_1][スカラ型へ複数の値を代入しようとする]{
my $player = 'reimu', 'alice', 'marisa';
say "player is $player";
say "player  type is " ~  $player.^name;
//}


//terminal[][出力結果]{
WARNINGS for /Users/anatofuz/src/github.com/anatofuz/yakumo-raku-master/src/chap04/item_assign1.raku:
Useless use of constant string "marisa" in sink context (lines 1, 1)
Useless use of constant string "alice" in sink context (lines 1, 1)
player is reimu
player  type is Str
//}

出力結果の@<code>{Useless~}が気になりますが、とりあえず変数playerにはreimuがStr型で代入されています。
さて@<code>{Useless~}のwarningは一体何の警告でしょうか。
まず @<code>{=}演算子の方が @<code>{,}よりも結合度が高いためにRakuは次のソースコードと等価に解釈します。

//list[][]{
my $player = 'reimu';
'marisa';
'alice';
//}

この場合marisa, aliceはただの文字列を評価したことになってしまい、 Sinkコンテキストが評価されてしまったために発生した警告です。
(Sinkコンテキストについては後ほど解説します)




==== 単一代入とリスト

なお右辺を@<code>{()}でくくった場合、 右辺値はリストになります。
リストそのものはList型クラスのインスタンスという扱いですので、スカラー値になります。
スカラー値であるため、 通常の単一代入(@<code>{$hoge = "hello}など) と同じ様にList型インスタンスそのものが代入されます。

//terminal[assign_scalar_ex3][()の有無で代入されるものが変わる]{
> my $scalar_list = 1,2,3; #()を付けずに代入
(1 2 3)
> $scalar_list; #代入された値はただのIntの値1つ
1 
> my $scalar_list = (1,2,3);
(1 2 3)
> $scalar_list; #代入された値はList型変数
(1 2 3)
//}

なおこの場合も@<code>{[]}演算子を利用することで、 リストの中からインデックスで要素にアクセスすることが可能です。


//terminal[assign_scalar_ex3-5][スカラー値のリストからのアクセス]{
> my $scalar_list = (1,2,3);
(1 2 3)
> $scalar_list[0]
1
//}


=== リスト代入 (list assignment)

リスト代入は左辺値がリストである場合に発生する代入方法です。

複数のスカラ変数の宣言と代入を行う際は、 個別に宣言する方法と、 リストとして纏めて宣言する方法があります。
個別宣言とリストで纏めて宣言した、次の2つの書き方は同じ意味となります。
//list[][]{
(my $one, my $two, $three, my $four) = (1,2,3,4);
my ($one, $two, $three, $four) = (1,2,3,4);
//}



==== リスト代入いろいろ

@<code>{()}はリストコンテキストに強制する@<kw>{,contextualizer}という振る舞いをしめします。

//terminal[][]{
> (my $c) = (1,2,3);
(1 2 3)
> $c.^name
List
//}


//list[][]{
> (my $c) = (1,2,3);
(1 2 3)
> $c
(1 2 3)
> (my $c) = 1,2,3;
(1 2 3)
> $c
(1 2 3)
>
+mumei+anatofuz$ raku
To exit type 'exit' or '^D'
> (my $a, my $b) = (1,2,3)
(1 2)
> $b
2
> (my $c) = (1,2,3);
(1 2 3)
//}


=== スカラーからリスト代入



=== 2番目の値を部分的にスカラに代入したい時

スカラ代入を使って、配列の特定の番号の要素を代入してみましょう。
リストの外側で@<code>{my}を使ってリストを宣言します。

リスト代入を使って、 スカラ変数にリストの要素を割り当てる場合は、各スカラ変数に名前をつける必要がありました。
//list[][]{
my ($a, $b, $c) = ('reimu', 'marisa', 'youmu');
//}

例えば上の例で、 リストの最初の要素であるreimuの値を今後スカラ変数として使わないケースを考えます。
右辺が配列であった場合、1番目の要素からのスライスを取る、 shiftを使って配列を破壊的に変更するなどの方法が考えられます。

今回はスカラ変数への代入時に、 最初の要素を代入する変数を用意せず、 最初の変数だけ代入しない方法で行ってみます。
reimuが代入されるであろう左辺の最初の変数である@<code>{$a}を、 無名変数@<code>{$}として宣言します。

//list[list_in_scalarrx1][リストの特定の要素を代入]{
my ($, $b, $c) = ('reimu', 'marisa', 'youmu');
//}

実際にREPLで確認してみます。

//terminal[list_in_scalarrx11][REPLで実行]{
> my ($, $b, $c) = ('reimu', 'marisa', 'youmu');
(reimu marisa youmu)
> $b 
marisa
> $c
youmu
> $
(Any)
//}

なお右辺が左辺の要素数より長い場合、自動的に長い分はカットされます。

//terminal[list_in_scalarrx12][右辺の要素が長い場合]{
> my ($, $b, $c) = ('reimu', 'marisa', 'youmu', 'sakuya'); # sakuyaは代入されない
(reimu marisa youmu)
> $c
youmu
//}


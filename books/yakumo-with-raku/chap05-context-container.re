= コンテキストとコンテナ

//abstract{
Rakuではコンテキストと呼ばれる仕組みが存在します。
これは自然言語の様に、文脈に応じて振る舞いが変更される機能です。
また、 Rakuの変数はコンテナと呼ばれるオブジェクトが深く関わっています。
この章ではコンテキストと、 Rakuの変数の実態であるコンテナについて追っていきます。
//}


== コンテキスト

Rakuでは@<kw>{コンテキスト, context}と呼ばれる概念が存在します。
コンテキストとは、 文脈という意味に相当します。

コンテキストという言葉はかなり便利な単語なので、 様々なプログラミング言語やOS、 ソフトウェアなどでコンテキストが登場します。
RakuのコンテキストはPerl5のコンテキストと同義であり、 呼び出しに応じて変数などの解釈が変化するものを指します。

Rakuでは6つのコンテキストが存在します。(@<table>{raku_context})

//table[raku_context][Rakuのコンテキスト]{
コンテキスト	役割
Sink	通常呼び出し
Numner	数値コンテキスト
String	文字列コンテキスト
Boolean	真偽値のコンテキスト
List	リストとして扱うコンテキスト
Item	単一の値として扱うコンテキスト
//}

=== Sink コンテキスト

Sinkコンテキストは対象となるオブジェクトを空打ちした場合に発生するコンテキストです。
他のプログラミング言語でのvoid関数の様に、 関数自体の返り値をなにかに代入することや、 評価をしない場合に発生します。

例えば次のコードでは、サブルーチンfooは呼び出し時に返り値を特に利用していないので、 Sinkコンテキストになります。

//listnum[sink_1][sinkコンテキストの例][perl6]{
sub foo {
  return 'hoge';
}

foo(); #値を使わないのでSinkコンテキスト

class Hoge  {}

Hoge; #値を使わないのでSinkコンテキスト(warningが発生する)

//}

//terminal[sink_test111][実行結果]{
$ raku chap04/sink_context.raku
WARNINGS for /Users/anatofuz/src/github.com/anatofuz/yakumo-raku-master/src/chap04/sink_context.raku:
Useless use of constant value Hoge in sink context (line 9)
//}

またsinkメソッドを利用すると、 強制的に続く式をSinkコンテキストで評価します。
返り値はNilが返ってきます。 


//terminal[sink_test1][sinkメソッドを利用すると代入文でも文が実行される]{
> constant hoge = sink say "hello";
hello
> hoge # hoge自体はNilが入っている
Nil
//}

著者としては意図的にSinkコンテキストを発生させるケースは稀であると思っており、 warningが発生したときに確認する程度でいいでしょう。

=== Number コンテキスト

@<kw>{数値のコンテキスト, Number}とはRakuで文字列型を四則演算しようとした場合に発生するコンテキストです。
Rakuは文字列型の中身が数値にキャストできると判断した場合、 自動的にその値をNumeric型のインスタンス、 つまり数値に変換します。
Numberコンテキストの為に、 文字列同士であっても、 明示的に数値型に型変換すること無く、 数値として計算することが可能です。

//listnum[number_1][Numberコンテキスト][perl6]{
my $one = "1"; #文字列として代入
my $two = "                  2                     "; #スペースをいれまくる

say $one + $two;


sub add($left, $right) {
    return $left + $right;
} 

say add("-10", 9); #混ぜてもいい
//}


//terminal[raku_number_1][実行結果]{
$ raku src/chap04/number_context.raku
3
-1
//}

マイナスの値でもよしなに計算されることがわかりました。


Numberコンテキストによって自動的に数値に変換が行われますが、明示的に数値型に変換したい場合があります。
文字列を数値に変換したい場合はprefixの@<code>{+}演算子を使うと可能です。@<fn>{raku_code_plus_prefix_hh1}

//terminal[raku_number_2][数値への変換]{
> +("10") #文字列10から数値の10に変換
10
> +("9")
9
> my $chiruno = +("9");
9
> $chiruno.^name; #型を確認するとIntになっている
Int
> $chiruno = "9";
9
> $chiruno.^name; #文字列を代入したのでStr型
Str
//}

なお残念がら漢字は対応していません。

//terminal[][]{
> +("九")
Cannot convert string to number: base-10 number must begin with valid digits or '.' in '⏏九' (indicated by ⏏)
  in block <unit> at <unknown file> line 1
//}


//footnote[raku_code_plus_prefix_hh1][実際はNumericメソッドが呼び出され、 Numeric型に変換されます]


== コンテナと変数

今までRakuの基本的な変数について見ていきました。
Rakuの各変数はインスタンスメソッドが使用できるあたり、 すべてがオブジェクトという言語かな? と思った方がいるかも知れません。

Rakuの変数はすべてがオブジェクトではなく、 実際はRakuの変数はRakuのオブジェクトへのポインタ(参照)となっています。
Rakuのソースコード内で変数宣言をした場合、 rakudoが所持しているシンボルテーブルに値が登録されます。
そして@<code>{$scalar}などの変数には、 実際の値へのポインタが代入されます。
この実際の値への参照のことを@<strong>{コンテナ (container)}と呼びます。

代入時に@<code>{=}ではなく、@<code>{:=}を利用した場合、 右辺値のデータに名前をつけることが可能です。
これは変数に対して値をコンテナを経由せずに紐付けることになるため、 束縛と言われます。

=== 文字列への束縛

束縛した値が文字列の場合、文字列はイミュータブルですので、再代入することが出来ません。 
(変数が指しているデータそのものを書き換えるためです)

//terminal[bind_test1][束縛の実験]{
> my $hoge := "hello"; #ここで$hogeを"hello"に束縛する
hello
> $hoge = 3;  #コンテナの値("hello")はイミュータブルなのでエラーが出る
Cannot assign to an immutable value
  in block <unit> at <unknown file> line 1
//}


=== 変数への束縛

これを応用して遊んでみましょう。
束縛する対象をとあるスカラー変数にし、そのスカラー変数を書き換えるとどうなるかを見てみます。

//listnum[bind_test2][束縛変数を書き換えてみる][perl6]{
my $reimu = "霊夢";

my $player := $reimu;

say $player; #この時点ではプレイヤーが束縛している$reimuの値は霊夢

$reimu = "魔理沙"; #このタイミングで$reimuの参照先が魔理沙に切り替わる
say $player;
//}


//terminal[bind_test2_term][実行結果]{
$ raku bind_test2.raku
霊夢
魔理沙
//}


驚くべきことに@<code>{$player}には手を付けていないにも関わらず、自機が霊夢から魔理沙に変化してしまっています。
これは@<code>{$player}が@<code>{$reimu}を束縛しており、@<code>{$reimu}自体はポインタになっており、ポインタが指す値が切り替わったためです。
先程の文字列の例の場合、文字列はイミュータブルでしたのでエラーが発生しましたが、束縛の対象が変数の場合、参照はミュータブルなのでこういうことが可能です。
驚くべきことに最後に@<code>{$player}自体を変更すると、@<code>{$reimu}の値も変更されます。

//listnum[bind_test3][束縛変数を書き換えてみる][perl6]{
my $reimu = "霊夢";

my $player := $reimu;

say $player; #この時点ではプレイヤーが束縛している$reimuの値は霊夢

$reimu = "魔理沙"; #このタイミングで$reimuの参照先が魔理沙に切り替わる
say $player;

$player = "妖夢";

say $player;
say $reimu;
//}

//terminal[bind_test3_term][実行結果]{
$ raku bind_test3.raku
霊夢
魔理沙
妖夢
妖夢
//}

関係性がわかりずらいので図にしてみました。
こうしてみると、束縛とは対象のデータに対して自分自身の名前をエイリアスすると言い換えることもできそうです。

//image[chap04-variables/container][束縛の関係図][scale=0.5,pos=H,border=on]

=== スカラーだけどリスト

さてここで配列への代入文を思い出してみましょう。

//list[][配列の初期化]{
my @array = (1,2,3);
//}

この代入の右辺値@<code>{(1,2,3)}はリスト形式、RakuのクラスでいうところのListです。
リストを@<code>{@}から始まる配列に代入すると、Array形式に変化します。 REPLで確認してみます。

//terminal[][代入すると型が変わる]{
> (1,2,3).^name;
List
> my @array = (1,2,3);
[1 2 3]
> @array.^name
Array
//}

実はArrayは要素をすべて1つずつコンテナ化して初期化するという機能があります。
代入文の変数のシジルが@であると、右辺値をArrayに型変換して代入します。

事実として、Listのままだと再代入することが不可能です。

//terminal[][listはイミュータブル]{
> (1,2,3)[0]
1
> (1,2,3)[0] = 9
Cannot modify an immutable List ((1 2 3))
  in block <unit> at <unknown file> line 1
//}


さて、このリスト形式、実はスカラー変数に束縛する事が可能です。

//terminal[][リストをスカラー変数に束縛してみる]{
> my $list = (1,2,3);
(1 2 3)
> $list[0]
1
> $list[0] = 0
Cannot modify an immutable List ((1 2 3))
  in block <unit> at <unknown file> line 1
//}


と、スカラー変数なのにリストを持つことが出来ます。
Rakuでプログラムを書く上で、代入する変数がスカラのシジルか配列のシジルかの違いによって、得られる値が微妙に異なることが解ってきました。

=== フラット、それはデリファレンスに似ている...

スカラー変数にリストをいれたままでは使いづらいので、配列に代入してみます。


//terminal[][束縛したリストを配列に代入]{
> my $list = (1,2,3);
(1 2 3)
> my @array = $list;
[(1 2 3)]
> @array
[(1 2 3)]
> @array.elems;
1
//}


おっと。このまま代入してしまうと、リスト型変数1つが配列に代入されてしまい、結果として要素数1の配列が出来てしまいました。
配列の初期化時にはこのような問題は発生しませんでしたが、今回の場合代入しようとしているデータ構造のシジルは@<code>{$}です。
実は@<code>{$}シジルは常に1つの値しか返さないため、 この場合では@<code>{(1,2,3)}というリストが1つの値として代入されてしまったのです。
また、List型そのものはスカラーデータであることも関係しています。
この問題を避けるには、リスト型変数の方で@<code>{flat}メソッドを使います。

//terminal[][束縛したリストをflatして配列に代入]{
> $list.flat
(1 2 3)
> my @array = $list.flat
[1 2 3]
> @array.elems;
3
//}

この状態だとリスト型変数がイテレーションされフラットなリストになり、それが配列へと代入されました。
他のやり方として@<code>{<>}演算子や@<code>{@}記号を利用することで同様のことが可能です。
Perl5に慣れている方は配列リファレンスのデリファレンスと考えればすんなり入るかなと思います。
//terminal[][flatの仕方いろいろ]{
> my @array  = @$hoge;
[1 2 3]
> my @array = $hoge<>;
[1 2 3]
//}

=== 改めて、コンテナとリスト

改めてコンテナとリスト、配列の関係についておさらいしましょう。
変数が持つコンテナの型を見るには@<code>{.VAR}に対して@<code>{.name}メソッドを実行します。

まず一般的な配列の初期化を行ってみます。

//listnum[container_array1][配列とコンテナと値の確認][perl6]{
my @array = (1,2,3,4,5), (1,2,3);

say '@array';
say "container: " ~ @array.VAR.^name;
say "self_type: " ~ @array.^name;

say "------";
say '@array[0]';

say "container: " ~ @array[0].VAR.^name;
say "self_type: " ~ @array[0].^name;

say "------";
say '@a0';

my @a0 = @array[0];

say "container: " ~ @0.VAR.^name;
say "self_type: " ~ @0.^name;
//}

//terminal[][実行結果]{
$ raku  container_array1.raku
@array
container: Array
self_type: Array
------
@array[0]
container: Scalar
self_type: List
------
@a0
container: List
self_type: List
//}


ソースコード4,5行目では@<code>{@array}自体がArray型であり、かつ指しているコンテナもArrayですので両方Arrayと表示されます。
Arrayの要素はスカラーであるため、@<code>{@array[0]}でアクセスした場合は、コンテナはスカラ型であり、値はList型となっています。
これを@<code>{@a0}に代入した場合、ListをArrayに変換していないため、 Array型には変換されません。
また、代入先がスカラの@<code>{$}シジルではなく、@<code>{@}シジルであるため、スカラ型からListへ変換が行われるため、@<code>{@a0}自体もListになります。


この様にRaku自体がどの様に変数や値を管理しているかについて知ると、Rakuプログラミングの世界が広がります。
(とはいえ、束縛などは普通にプログラミングする上ではあまり使わないかなという印象です)

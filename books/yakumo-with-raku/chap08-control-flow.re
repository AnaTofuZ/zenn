= ループいろいろ

== for

Rakuでのforループは、 listなどの集合の各要素に対して繰り返しを行うループです。
いわゆるforeachに該当します。

for文は @<b>{for @リスト -> $ループ時に代入する変数 }の順で記述します。

//listnum[for_exam0][for文][perl6]{
my @data = (1,2,3);
for @data -> $i {
    say $i;
}
//}

範囲演算子(@<code>{..}演算子)を利用してRangeクラスのインスタンスを作り、 これをループさせることも可能です。

//listnum[for_exam1][範囲演算子を使った場合のfor文][perl6]{
for 1..10 -> $i {
    say $i;
}
//}

代入する変数を省略した場合、Perl5と同様に無名変数@<b>{$_}に値が代入されます。
この$_のことをRakuではtopicと呼びます。

//listnum[for_exam2][topicを利用した場合のfor文][perl6]{
my @data = 1..10;
for @data {
    say $_;
}
//}

また後置・接尾辞(postfix)の形でも利用出来ます

//listnum[for_exam3][postfixの形のfor文][perl6]{
my @data = 1..10;
$_.say for @data;
//}

topicの変数がデフォルト変数の場合、さらに省略することが可能です。

//listnum[for_exam4][$_を省略した場合のfor文][perl6]{
my @data = 1..10;
.say for @data;
//}

直接範囲演算子を使った場合でも実行可能です。

//listnum[for_exam5][$_を省略し、..演算子を使った場合のfor文][perl6]{
.say for 1..10;
//}

さらにdo演算子を文の前に書くことで、for文の各ループでの結果を代入することが可能です。
具体例を見てみましょう。
//listnum[loop_exam1_do1][do forで結果を受け取る][perl6]{
my @yakumo = (qw/yukari ran chen/);

my $counter = 0;

my $result = do for @yakumo -> $member {
    $counter++;
    "Hello! $member!";
}

say "counter = $counter";
say "result = $result";
//}


//terminal[do_for_term1][実行結果]{
$ raku do_for.raku
counter = 3
result = Hello! yukari! Hello! ran! Hello! chen!
//}

この様にfor文で最後に評価した文字列がリストになり、 その値がスカラ型に束縛されresultでは一つの変数の様に扱えます。@<fn>{raku_do_for_raku_fn}
スカラ型でなく配列のシジルで代入すると、それぞれの結果がリストにpushされていることがわかります。
実際の受け取った値を配列にして、for文で確認してみます。

//listnum[loop_exam1_do2][do forで結果を配列で受け取る][perl6]{
my @yakumo = (qw/yukari ran chen/);

my $counter = 0;

my @result = do for @yakumo -> $member {
    $counter++;
    "Hello! $member!";
}

say "counter = $counter";
.say  for @result;
//}


//terminal[do_for_term2][実行結果]{
$ raku do_for2.raku
counter = 3
Hello! yukari!
Hello! ran!
Hello! chen!
//}

//footnote[raku_do_for_raku_fn][そのため厳密には@<code>{$result}の型はListとなります。 これは @<code>{say $result.^name;}などとするとわかります]

== loop

RakuではC言語スタイルのループ構文は@<B>{loop}文を使うことで表現できます。

//listnum[loop_exam1][loop文の例][perl6]{
loop (my $i = 0; $i < 10; $i++) {
    $i.say;
}
//}

loopの()を省略するか、中身を書かない場合は無限ループが記述出来ます。


//listnum[loop_exam1][loop文のでの無限ループ][perl6]{
loop (;;) {
  say "infinity loop!";
}

loop {
  say "infinity loop!";
}
//}

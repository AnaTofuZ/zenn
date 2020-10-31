= サブルーチン

Rakuではオブジェクトやクラスに紐づく@<strong>{メソッド}、それとは無関係に呼び出すことができる@<strong>{関数(サブルーチン,subs)}と呼ばれる大きく分けて2種類のルーチンが存在しています。
メソッドはクラスにスコープを持ちますが、 サブルーチンの場合はレキシカルスコープ(myで宣言した変数と同様のスコープ)を持ちます。

== サブルーチンの宣言

サブルーチンの宣言には@<code>{sub}キーワードを利用します。


== サブルーチンをオブジェクトに

実は@<code>{sub}はSub型のインスタンスを返します。
そのため、サブルーチンの宣言を変数で受け取ることが可能です。


== ラムダ、ブロック、Signature


@<code>{->}記法は、 新しいブロックに入るまでを関数の引数シグネチャとして宣言できる記法です。
@<code>{->}自体も、一種のブロックとなります。

実は今まで見てきた中で、すでにifやfor, whileなどで利用しています。
for文の場合は、次の様に利用していました。

//list[][]{
for @array -> $item {
    say $item;
}
//}

for文の宣言を一行に書いてみましょう。

//list[][]{
for @array -> $item { say $item }
//}

実はこの@<code>{->}によって、 @<code>{$item}の部分が1つのブロックとなります。また、@<code>{->}によって引数シグネチャに設定されています。
続く@<code>{{say $item\}}は@<code>{{\}}によって新たなブロックとして宣言されています。

//terminal[][実行例]{
> my $hoge = -> ($a,$b) { $a+$b}
-> $ ($a, $b) { #`(Block|140618718453320) ... }
> $hoge(2,3)
Cannot unpack or Capture `2`.
To create a Capture, add parentheses: \(...)
If unpacking in a signature, perhaps you needlessly used parentheses? -> ($x) {} vs. -> $x {}
or missed `:` in signature unpacking? -> &c:(Int) {}
  in block  at <unknown file> line 1
  in block <unit> at <unknown file> line 1

> $hoge
-> $ ($a, $b) { #`(Block|140618718453320) ... }

> say $hoge($(2,3));
5
> my $hoge = -> $a,$b { $a+$b}
-> $a, $b { #`(Block|140618797956864) ... }
> say $hoge($(2,3));
Too few positionals passed; expected 2 arguments but got 1
  in block  at <unknown file> line 1
  in block <unit> at <unknown file> line 1

> say $hoge(2,3);
5
//}


== Parameter

実はRakuの関数の引数は、それ自体はParameterというクラスのインスタンスになっています。

= 演算子

//abstract{
Rakuの演算子はジャンルに富んでいます。
...というのも、 Rakuはプログラマが自由に演算子を定義することが可能であり、 かつ柔軟に設定することが可能であるためです。
ここでは公式ドキュメントなどで紹介されている、 組み込み演算子をいくつか紹介します。
//}


== 演算子のジャンル

Rakuでは演算子はいくつかの種類に分類する事が可能です。

//table[raku_opecode_list1][Rakuの演算子の種類]{
名前	日本語	種類	具体例
prefix	接頭辞	@<code>{+term}	@<code>{++}
postfix	接尾辞	@<code>{term+}	@<code>{[]}
infix	接中辞	@<code>{term1 + term2}	@<code>{=}
//}


== infix (接中辞)

=== : 

infix(接中辞)の@<code>{:}演算子は、@<code>{,}演算子に似ていますが、関数呼び出しの引数内で利用します。
この演算子の直前のオブジェクトを@<kw>{呼び出し元,invocant}として扱い、 関数呼び出しであるものをメソッド呼び出しに変更する役割があります。
Perl5のプログラミングの経験がある方は、 「間接オブジェクト形式を実行することができる演算子」と考えれば理解がしやすいでしょう。
これは言葉で説明するより具体例を見たほうがわかりやすいので、 早速コードを見てみましょう。

//listnum[infix_:_op][infix : 演算子を利用して呼び出し方を変えてみる][perl6]{
class Marisa {
    method master_spark($target) {
        "Attack $target with Master Spark!"
    }
}

my $mari = Marisa.new;

say $mari.master_spark("youmu");
say master_spark($mari: "youmu");
say master_spark(Marisa: "youmu");
//}

//terminal[infix_:_op_exec][実行結果]{
$ raku invocant_operatof_infix.raku
Attack youmu with Master Spark!
Attack youmu with Master Spark!
Attack youmu with Master Spark!
//}

上の例では@<code>{master_spark}はMarisaクラスのメソッドです。
最初のsayではMarisaのインスタンスである@<code>{$mari}からメソッド呼び出しの形で実行しています。
次のsayでは @<code>{master_spark($mari:}となっており、 @<code>{:}演算子によって直前の@<code>{$mari}がinvocantとなります。
これらは@<code>{master_spark}の引数内で宣言されているため、 関数名の@<code>{master_spark}が@<code>{:}演算子によってinvocantのクラスのメソッドとなる。
つまり@<code>{$mari.master_spark()}と実行した事と同じ事になります。
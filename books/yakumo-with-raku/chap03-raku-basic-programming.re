= rakuコマンドとプログラム

//abstract{
ここではRakuを使う上で避けては通れないrakuコマンドの詳細について見ていきます
//}

== Rakuプログラムの拡張子

C言語では@<code>{.c}、 Perlなら@<code>{.pl}の様にプログラムには推奨されている拡張子が存在します。
Rakuの場合は@<strong>{単体のスクリプトの場合}は@<code>{.raku}が推奨されています。
以前までPerl6だった影響があるため、 各種文献やインターネットに出回っているソースコードでは@<code>{.p6}や@<code>{.pl}、 @<code>{pl6}などの拡張子が使われているものも存在します。
p6やplなどのPerl6由来の拡張子は今後非推奨になります。@<fn>{raku_version_pl}


//footnote[raku_version_pl][具体的に言うと6.f以降は非推奨になる模様です]

== コメント

Rakuではコメントを利用することが出来ます。
コメントは実行時に無視されます。

=== 一行コメント

Rakuでは @<code>{#}文字から改行までコメント扱いになります。

//listnum[raku_comment_one][1行コメント][perl6]{
say "hello!"; #ここからコメント
#これもコメント
//}

=== 複数行コメント

Rakuでは @<code>{#`}とカッコを使うと複数行コメントが可能です。
カッコは開いたカッコで閉じる必要があります。

//listnum[raku_comment_some][複数行コメント][perl6]{
if #`( カッコの間がコメント ) True {
  #`[
 ここも コメント
  ]
}
//}

=== podを使ったコメント

PerlでのテクニックとしてPODを使って複数行コメントをするものが有りました。
Rakuでもほぼ同様の事が可能です。

//listnum[raku_comment_pod][podを使ったコメント][perl6]{

say "hello!";
=begin comment 

この中はコメント

=end comment
//}

== raku(perl6)コマンド

Raku言語をRakudo処理系で構築した場合、 @<code>{raku}コマンドを用いてプログラムを実行します。
@<code>{raku}コマンド自体はシェルスクリプトとなっており、 基本的にはMoarVMを呼び出すのみとなっています。
Rakudoの下位言語であるNQPも@<code>{nqp}コマンドを用いることで実行する事が可能です。

//terminal[raku_exec_1_comd][rakuの実行]{
$ raku
You may want to `zef install Readline` or `zef install Linenoise` or use rlwrap for a line editor

To exit type 'exit' or '^D'
> % 
//}


//terminal[raku_exec_2_comd][nqpの実行]{
$ nqp
>
//}


スクリプトに書いたプログラムを実行する場合は @<code>{$raku src.raku}の様に実行します。

//terminal[raku_exec_3_comd][rakuでのスクリプトの実行]{
$ cat hello.raku
say "Hello, World!!";
$ raku hello.raku
Hello, World!!
//}


== コマンドオプションたち

@<code>{raku}とプログラム名の間にいくつかオプションを指定することが可能です。
RakuはPerlの流れを強く受け継いでいる言語ですので、 Perl5に詳しい方は同じ様なオプションが使用可能ですが、 いくつか面白いオプションが存在します。

=== -c オプション

@<code>{-c}オプションはシンタックスチェックを実行するオプションです。実際にソースコードの内容は実行されません。
試しに以下のような正常なコードを入力してみます。

//listnum[_c_option_perl][Syntax OKなRakuコード][perl6]{
"This is OK!".say;
//}

//terminal[_c_option_term][SyntaxOKな場合]{
$ raku -c  syntax_ok.raku
Syntax OK
//}

この様にSyntax OKと出力され、 構文に問題がないことがわかります。

次に先程のソースコードの右側のダブルクォーテーションを外して見ましょう。

//listnum[_c_option_perl2][Syntax NGなRakuコード][perl6]{
"This is OK!.say;
//}


//terminal[_c_option_term2][SyntaxNGな場合]{
$ raku -c syntax_ng.raku
===SORRY!=== Error while compiling /Users/anatofuz/src/github.com/anatofuz/yakumo-raku-master/src/chap3/syntax_ng.raku
Unable to parse expression in double quotes; couldn't find final '"' (corresponding starter was at line 1)
at /Users/anatofuz/src/github.com/anatofuz/yakumo-raku-master/src/chap3/syntax_ng.raku:2
------> <BOL>⏏<EOL>
    expecting any of:
        double quotes
        statement list
        term
//}


エラーの場合このような表示で出力されます。

なお@<code>{-c}オプションはあくまで構文上の問題のみ解決するため、 現状では型エラーなどは検出不可能です。
試しに後述するサブルーチンの引数の型を指定する方法で、 Int型変数を2つ受け取るadd関数に文字列を送ってみます。

//listnum[_c_option_perl3][Int型変数を2つ受け取る関数に文字列を渡す][perl6]{
$ cat invalid_type_arg.raku
sub add(Int $n, Int $m) {
    return $n+$m;
}

say "hello!";
add(3,"hoge");
//}

このコードを実行した場合、コンパイルタイムにエラーが発生します。(そのために6行目で出力しようとしているhelloという文字列が出力されません)

//terminal[_c_option_term3][引数の型エラーが発生するコードの実行例]{
$ raku invalid_type_arg.raku
===SORRY!=== Error while compiling invalid_type_arg.raku
Calling add(Int, Str) will never work with declared signature (Int $n, Int $m)
at invalid_type_arg.raku:6
------> <BOL>⏏add(3,"hoge");
//}

しかし現状このエラーは@<code>{-c}オプションでは見逃されます。

//terminal[_c_option_term4][型エラーが発生する場合でも-cでは検出出来ない]{
$ raku -c invalid_type_arg.raku
Syntax OK
//}

=== --doc オプション

@<code>{--doc}オプションは、与えられたRakuプログラムの中からPOD6と呼ばれる形式で書かれたドキュメントをレンダリングしてくれるオプションです。
POD6とはPerl5のPODとほぼ等価なマークアップ言語であり、 ドキュメントなどを書くための形式です。
Perl5に慣れている方は、いわゆるperldocコマンドと等価なものと考えるとわかりやすいでしょう。

//listnum[_pod_exam1][POD形式のサンプル][perl6]{
$ cat src/chap3/doc.raku
=begin pod

=head1 Yakumo::Ran
=item かわいい
=item きつね

=end pod
//}

試しにPODで上のようなドキュメントを書いてみました。これをdocオプションで実行してみましょう

//terminal[__pod_output][POD形式のレンダリング]{
$ raku --doc src/chap3/doc.raku
Yakumo::Ran

  * かわいい

  * きつね
//}

この様にターミナルでも見やすい形式にレンダリングしてくれます。

=== --profileオプション

@<code>{--profile}オプションをつけるとRakuの標準プロファイラが起動し、 スクリプトの実行内容をプロファイリングしてくれます。
@<code>{--profile}のみ指定するとHTML形式でプロファイル結果が出力され、 実行時に呼び出したメソッドの処理時間がグラフ化されたり、 GCや最適化、 CallFramesなどについて詳細な情報が出力されます。

//terminal[exec_profile_op][プロファイリングオプションを付けた上での実行]{
$ ls
hello.raku
$ raku --profile hello.raku
Hello, World!!
Writing profiler output to profile-1583648514.4093318.html
$ ls
hello.raku                       profile-1583648514.4093318.html
//}

@<code>{--profile=output.json}などと@<code>{=}の後にファイル名を指定することが可能です。
このファイル名の拡張子をjson, sqlにすると、 それぞれjson形式及びSQLでプロファイリングの結果が出力されます。 

//terminal[exec_profile_op2][プロファイリングオプションでjsonを生成する実行]{
$ raku --profile=prof.json hello.raku
Hello, World!!
Writing profiler output to prof.json
//}

//listnum[profile_json][生成されたjsonの一部][json]{
  {
    "total_time": 11837,
    "thread": 1,
    "start_time": 0,
    "spesh_time": 0,
    "parent": 0,
    "gcs": [],
    "call_graph": {
      "inclusive_time": 3634,
      "id": "0",
      "highest_child_id": 54,
      "first_entry_time": 0,
      "exclusive_time": 9,
//}

//terminal[exec_profile_op3][プロファイリングオプションでsqlを生成する実行]{
$ raku --profile=prof.sql hello.raku
Hello, World!!
Writing profiler output to prof.sql
//}

//listnum[profile_sql][生成されたSQLの一部][sql]{
BEGIN;
CREATE TABLE types(id INTEGER PRIMARY KEY ASC, name TEXT, extra_info JSON, type_links JSON);
CREATE TABLE routines(id INTEGER PRIMARY KEY ASC, name TEXT, line INT, file TEXT);
CREATE TABLE gcs(time INT, retained_bytes INT, promoted_bytes INT, gen2_roots INT, stolen_gen2_roots INT, full INT, responsible INT, cleared_bytes INT, start_time INT, sequence_num INT, thread_id INT, PRIMARY KEY(sequence_num, thread_id));
CREATE TABLE calls(id INTEGER PRIMARY KEY ASC, parent_id INT, routine_id INT, osr INT, spesh_entries INT, jit_entries INT, inlined_entries INT, inclusive_time INT, exclusive_time INT, entries INT, deopt_one INT, deopt_all INT, rec_depth INT, first_entry_time INT, highest_child_id INT, FOREIGN KEY(routine_id) REFERENCES routines(id));
CREATE TABLE profile(total_time INT, spesh_time INT, thread_id INT, parent_thread_id INT, root_node INT, first_entry_time INT, FOREIGN KEY(root_node) REFERENCES calls(id));
//}


=== -eオプションとその周辺

@<code>{-e}オプションは続く文字列をRakuのプログラムとして認識するオプションです。
Perl5を書く皆さんならおなじみのワンライナーオプションです。

//terminal[_e_option_ex1][-eオプションでワンライナー]{
$ raku -e 'say "hello!"'
hello!
//}

@<code>{-e}の周辺オプションである@<code>{-n}や@<code>{-p}などもPerl5と同様に使うことが可能です。

//terminal[_e_option_ex2][標準入力で与えられた文字列をスペース区切りで総和を求めるワンライナー]{
$ echo '1 2 3 4' | perl6 -ne 'say [+] .split(" ")'
10
//}

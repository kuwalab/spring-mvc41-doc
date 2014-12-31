= カスタムタグ

== Formタグ

==={033} form:inputタグ

@<b>{タグ【033】}

form:inputタグは、HTMLの<input type="text">タグを生成します。

その要素の内、単純にHTMLの属性に置き換えられるものは、以下の属性です。cssClassやcssStyleはそれぞれclass、style属性に置き換えられます。

//table[033-form:input1][HTMLの属性]{
属性	説明
-------------------------------------------------------------
accesskey		HTML標準のaccesskey属性
alt				HTML標準のalt属性
autocomplete	HTML標準のautocomplete属性
cssClass		HTML標準のclass属性
cssStyle		HTML標準のsytle属性
dir				HTML標準のdir属性
disabled		HTML標準のdisabled属性
id				HTML標準のid属性
lang			HTML標準のlang属性
maxlength		HTML標準のmaxlength属性
readonly		HTML標準のreadonly属性
size			HTML標準のsize属性
tabindex		HTML標準のtabindex
title			HTML標準のtitle属性
//}

その他、JavaScriptのDOMレベル0イベントとして以下の属性が用意されています。それぞれ同名の属性になります。

//table[033-form:input2][イベントハンドラの属性]{
属性
-------------------------------------------------------------
onblur
onchange
onclick
ondblclick
onfocus
onkeydown
onkeypress
onkeyup
onmousedown
onmousemove
onmouseout
onmouseover
onmouseup
onselect
//}

残りがSpring用の属性になります。

//table[033-form:input3][Springの属性]{
属性			説明
-------------------------------------------------------------
cssErrorClass	Validationのエラー時のclass属性
htmlEscape		HTMLのエスケープをするかどうか。デフォルトはtrue
path			関連付けるModelの名前
//}

サンプルを見ていきます。まず、コントローラーで使用するモデルです。

//list[033-C033Model.java][C033Model.java]{
package com.example.spring.controller.c033;

public class C033Model {
    private String name;
    private Integer price;
    private Integer listPrice;

    public C033Model(String name, Integer price, Integer listPrice) {
        this.name = name;
        this.price = price;
        this.listPrice = listPrice;
    }

    // setter、getterは省略
}
//}

サンプルのコントローラーです。

//list[033-C033Contoller.java][C033Controller.java]{
package com.example.spring.controller.c033;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestMapping;

@Controller
@RequestMapping("/c033")
public class C033Controller {
    @RequestMapping("/input")
    public String input(Model model) {
        C033Model c033Model = new C033Model("よく分かるSpring<&>", 2000, 2500);
        model.addAttribute("c033Model", c033Model);
        return "c033/input";
    }
}
//}

コントローラではformで利用する値をModelに格納しています。

カスタムタグを使用しているJSPです。

//list[033-input.jsp][input.jsp]{
<%@page contentType="text/html; charset=utf-8" %><%--
--%><!DOCTYPE html>
<html>
 <head>
  <meta charset="utf-8">
  <title>サンプル</title>
 </head>
 <body>
書名: <form:input path="c033Model.name" size="20" /><br>
価格: <form:input path="c033Model.price" size="10" maxlength="6" readonly="true" /><br>
定価: <form:input path="c033Model.listPrice" size="10" disabled="true" /><br>
 </body>
</html>
//}

path属性で、モデルの値とタグを関連付けます。Modelに設定されている値がformの初期値となります。

実際に動作させ、出力されるHTMLは以下のようになります。

//list[033-html][出力されるHTML]{
<!DOCTYPE html>
<html>
 <head>
  <meta charset="utf-8">
  <title>サンプル</title>
 </head>
 <body>
書名: <input id="name" name="name" type="text" value="よく分かるSpring&lt;&amp;&gt;"
       size="20"/><br>
価格: <input id="price" name="price" readonly="readonly" type="text" value="2000"
       size="10" maxlength="6"/><br>
定価: <input id="listPrice" name="listPrice" disabled="disabled" type="text"
       value="2500" size="10"/><br>
 </body>
</html>
//}

==={034} form:passwordタグ

@<b>{タグ【034】}

form:passwordタグは、HTMLの<input type="password">タグを生成します。

指定できる属性はshowPassword以外はform:inputと同じです。

その要素の内、単純にHTMLの属性に置き換えられるものは、以下の属性です。cssClassやcssStyleはそれぞれclass、style属性に置き換えられます。

//table[034-form:password1][HTMLの属性]{
属性	説明
-------------------------------------------------------------
accesskey		HTML標準のaccesskey属性
alt				HTML標準のalt属性
autocomplete	HTML標準のautocomplete属性
cssClass		HTML標準のclass属性
cssStyle		HTML標準のsytle属性
dir				HTML標準のdir属性
disabled		HTML標準のdisabled属性
id				HTML標準のid属性
lang			HTML標準のlang属性
maxlength		HTML標準のmaxlength属性
readonly		HTML標準のreadonly属性
size			HTML標準のsize属性
tabindex		HTML標準のtabindex
title			HTML標準のtitle属性
//}

その他、JavaScriptのDOMレベル0イベントとして以下の属性が用意されています。それぞれ同名の属性になります。

//table[034-form:password2][イベントハンドラの属性]{
属性
------------------------------------------------------------
onblur
onchange
onclick
ondblclick
onfocus
onkeydown
onkeypress
onkeyup
onmousedown
onmousemove
onmouseout
onmouseover
onmouseup
onselect
//}

残りがSpring用の属性になります。

//table[034-form:password3][Springの属性]{
属性			説明
-------------------------------------------------------------
cssErrorClass	Validationのエラー時のclass属性
htmlEscape		HTMLのエスケープをするかどうか。デフォルトはtrue
path			関連付けるModelの名前
showPassword	パスワードを表示（value属性に出力）するか
//}

コントローラで使う、Modelです。パスワードのみを格納します。

//list[034-C034Model.java][C034Model.java]{
package com.example.spring.controller.c034;

public class C034Model {
    private String password;

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }
}
//}

サンプルのコントローラです。

//list[034-C034Controller.java][C034Controller.java]{
package com.example.spring.controller.c034;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestMapping;

@Controller
@RequestMapping("/c034")
public class C034Controller {
    @RequestMapping("/password")
    public String password(Model model) {
        C034Model c034Model = new C034Model();
        ;
        c034Model.setPassword("password");
        model.addAttribute("c034Model", c034Model);
        return "c034/password";
    }
}
//}

コントローラではformで利用する値をModelに格納しています。

カスタムタグを使用しているJSPです。

//list[034-password.jsp][password.jsp]{
<%@page contentType="text/html; charset=utf-8" %><%--
--%><!DOCTYPE html>
<html>
 <head>
  <meta charset="utf-8">
  <title>サンプル</title>
 </head>
 <body>
password: <form:password path="c034Model.password" /><br>
showPassword=true: <form:password path="c034Model.password" showPassword="true" /><br>
 </body>
</html>
//}

showPasswordを設定しない場合にはpath属性の値は出力されません。逆にshowPasswordをtrueにするとvalueに値が出力されます。

==={035} form:hiddenタグ

@<b>{タグ【035】}

form:hiddenタグは、HTMLの<input type="hidden">タグを生成します。

その要素の内、単純にHTMLの属性に置き換えられるものは、以下の属性です。

//table[035-form:hidden1][HTMLの属性]{
属性	説明
-------------------------------------------------------------
id		HTML標準のid属性
lang	HTML標準のlang属性
//}

残りがSpring用の属性になります。

//table[035-form:hidden2][Springの属性]{
属性			説明
-------------------------------------------------------------
htmlEscape		HTMLのエスケープをするかどうか。デフォルトはtrue
path			関連付けるModelの名前
//}

コントローラーで使用するModelです。

//list[035-C035Model.java][C035Model.java]{
package com.example.spring.controller.c035;

public class C035Model {
    private String name;
    private Integer price;

    public C035Model(String name, Integer price) {
        super();
        this.name = name;
        this.price = price;
    }

    // setter、getterは省略
}
//}

サンプルのコントローラーです。

//list[035-C035Controller.java][C035Controller.java]{
package com.example.spring.controller.c035;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestMapping;

@Controller
@RequestMapping("/c035")
public class C035Controller {
    @RequestMapping("/hidden")
    public String password(Model model) {
        C035Model c035Model = new C035Model("よくわかるSpring", 2500);
        model.addAttribute("c035Model", c035Model);

        return "c035/hidden";
    }
}
//}

コントローラではformで利用する値をModelに格納しています。

カスタムタグを使用しているJSPです。

//list[035-hidden.jsp][hidden.jsp]{
<%@page contentType="text/html; charset=utf-8" %><%--
--%><!DOCTYPE html>
<html>
 <head>
  <meta charset="utf-8">
  <title>サンプル</title>
 </head>
 <body>
書名: <form:hidden path="c035Model.name" /><br>
価格: <form:hidden path="c035Model.price" />
 </body>
</html>
//}



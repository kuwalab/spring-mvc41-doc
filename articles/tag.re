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

==={036} form:checkboxタグ

@<b>{タグ【036】}

form:checkboxタグは、HTMLの<input type="checkbox">タグを生成します。

その要素の内、単純にHTMLの属性に置き換えられるものは、以下の属性です。cssClassやcssStyleはそれぞれclass、style属性に置き換えられます。

//table[036-form:checkbox1][HTMLの属性]{
属性		説明
-------------------------------------------------------------
accesskey	HTML標準のaccesskey属性
cssClass	HTML標準のclass属性
cssStyle	HTML標準のsytle属性
dir			HTML標準のdir属性
disabled	HTML標準のdisabled属性
id			HTML標準のid属性
lang		HTML標準のlang属性
tabindex	HTML標準のtabindex
title		HTML標準のtitle属性
value		HTML標準のvalue属性
//}

その他、JavaScriptのDOMレベル0イベントとして以下の属性が用意されています。それぞれ同名の属性になります。

//table[036-form:checkbox2][イベントハンドラの属性]{
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
//}

残りがSpring用の属性になります。

//table[036-form:checkbox3][Springの属性]{
属性			名前
-------------------------------------------------------------
cssErrorClass	Validationのエラー時のclass属性
htmlEscape		HTMLのエスケープをするかどうか。デフォルトはtrue
label			HTMLのlabel要素を作成し、チェックボックスと関連付ける
path			関連付けるModelの名前
//}

まず、コントローラで使用するモデルです。

//list[036-C036Model.java][C036Model.java]{
package com.example.spring.controller.c036;

public class C036Model {
    private boolean check;

    public boolean isCheck() {
        return check;
    }

    public void setCheck(boolean check) {
        this.check = check;
    }
}
//}

サンプルのコントローラです。

//list[036-C036Controller.java][C036Controller.java]{
package com.example.spring.controller.c036;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestMapping;

@Controller
@RequestMapping("/c036")
public class C036Controller {
    @RequestMapping("/checkbox")
    public String checkbox(Model model) {
        C036Model c036Model = new C036Model();
        c036Model.setCheck(true);
        model.addAttribute("c036Model", c036Model);
        return "c036/checkbox";
    }

    @RequestMapping("/checkboxRecv")
    public String checkboxRecv(String check, Model model) {
        model.addAttribute("recvData", check);
        return "c036/checkboxRecv";
    }
}
//}

コントローラではformで利用する値をModelに格納しています。

カスタムタグを使用しているJSPです。

//list[036-checkbox.jsp][checkbox.jsp]{
<%@page contentType="text/html; charset=utf-8" %><%--
--%><!DOCTYPE html>
<html>
 <head>
  <meta charset="utf-8">
  <title>サンプル</title>
 </head>
 <body>
  <form action="checkboxRecv">
   <form:checkbox path="c036Model.check" label="チェック"/><br>
   <input type="submit" value="送信">
  </form>
 </body>
</html>
//}

受信するcheckboxRecv.jspです。

//list[036-checkboxRecv.jsp][checkboxRecv.jsp]{
<%@page contentType="text/html; charset=utf-8" %><%--
--%><!DOCTYPE html>
<html>
 <head>
  <meta charset="utf-8">
  <title>サンプル</title>
 </head>
 <body>
受信データ: <c:out value="${recvData}" /><br>
 </body>
</html>
//}

実際に動作させ、出力されるHTMLは以下のようになります（見やすくするために改行を入れています）。

//list[036-html][出力されるHTML]{
<!DOCTYPE html>
<html>
 <head>
  <meta charset="utf-8">
  <title>サンプル</title>
 </head>
 <body>
  <form action="checkboxRecv">
   <input id="check1" name="check" type="checkbox" value="true" checked="checked"/>
   <label for="check1">チェック</label><input type="hidden" name="_check" value="on"/><br>
   <input type="submit" value="送信">
  </form>
 </body>
</html>
//}

label属性を指定していると、HTMLのlabel要素が出力されます。

==={037} form:checkboxesタグ

@<b>{タグ【037】}

form:checkboxesタグは、HTMLの&lt;input type="checkbox"&gt;タグのまとまりを生成します。

その要素の内、単純にHTMLの属性に置き換えられるものは、以下の属性です。cssClassやcssStyleはそれぞれclass、style属性に置き換えられます。

//table[037-form:checkboxes1][HTMLの属性]{
属性		説明
-------------------------------------------------------------
accesskey	HTML標準のaccesskey属性
cssClass	HTML標準のclass属性
cssStyle	HTML標準のsytle属性
dir			HTML標準のdir属性
disabled	HTML標準のdisabled属性
id			HTML標準のid属性
lang		HTML標準のlang属性
tabindex	HTML標準のtabindex
title		HTML標準のtitle属性
//}

その他、JavaScriptのDOMレベル0イベントとして以下の属性が用意されています。それぞれ同名の属性になります。

//table[037-form:checkboxes2][イベントハンドラの属性]{
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
//}

残りがSpring用の属性になります。

//table[037-form:checkboxes3][Springの属性]{
属性			説明
-------------------------------------------------------------
cssErrorClass	Validationのエラー時のclass属性
delimiter		チェックボックスの間の区切り文字。デフォルトはなし
element			それぞれのcheckboxを囲む要素。デフォルトはspan
htmlEscape		HTMLのエスケープをするかどうか。デフォルトはtrue
itemLabel		labelを出力するitemsで指定したクラスのプロパティ名
items			checkboxを作るための配列やMap
itemValue		valueを出力するitemsで指定したクラスのプロパティ名
path			関連付けるModelの名前
//}

実際の例を確認していきます。まずは、一つのチェックボックスを表すモデルクラスです。isbnをvalue、nameをラベルに使用します。

//list[037-C037Model.java][C037Model.java]{
package com.example.spring.controller.c037;

public class C037Model {
    private String isbn;
    private String name;

    // setter、getterは省略
}
//}

サンプルのコントローラです。

//list[037-C037Controller.java][C037Controller.java]{
package com.example.spring.controller.c037; 
import java.util.ArrayList;
import java.util.List;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;

@Controller
@RequestMapping("/c037")
public class C037Controller {
    @RequestMapping("/checkboxes")
    public String checkboxes(Model model) {
        List<C037Model> c037ModelList = new ArrayList<>();

        c037ModelList.add(new C037Model("123", "よく分かるSpring"));
        c037ModelList.add(new C037Model("456", "よく分かるJava"));
        c037ModelList.add(new C037Model("789", "よく分かるSpring MVC"));

        model.addAttribute("c037ModelList", c037ModelList);

        C037Form c037Form = new C037Form();
        c037Form.setSelectedIsbn(new String[] { "456" });
        model.addAttribute("c037Form", c037Form);
        return "c037/checkboxes";
    }

    @RequestMapping("/checkboxesRecv")
    public String checkboxesRecv(
            @RequestParam(required = false) String[] selectedIsbn, Model model) {
        model.addAttribute("isbns", selectedIsbn);
        return "c037/checkboxesRecv";
    }
}
//}

checkboxesメソッドではチェックボックスとして表示するためにBookクラスのオブジェクトのリストを作成しています。また、チェックボックスの初期値として、BookFormクラスのselectedIsbnに選択状態にするチェックボックスのisbn（value）を指定します。初期値を設定しない場合には、nullか空のString配列を渡してください。

カスタムタグを使用しているJSPです。

//list[037-checkboxes.jsp][checkboxes.jsp]{
<%@page contentType="text/html; charset=utf-8" %><%--
--%><!DOCTYPE html>
<html>
 <head>
  <meta charset="utf-8">
  <title>サンプル</title>
 </head>
 <body>
  <form action="checkboxesRecv">
   <form:checkboxes path="c037Form.selectedIsbn" items="${c037ModelList}"
    itemLabel="name" itemValue="isbn" delimiter=" " /><br>
   <input type="submit" value="送信">
  </form>
 </body>
</html>
//}

JSPではチェックボックスのリストをitems属性で指定します。itemLabelとitemValueでチェックボックスのラベルとvalueを取得するフィールド名を指定します。

受信するcheckboxesRecv.jspです。

//list[037-checkboxesRecv.jsp][checkboxesRecv.jsp]{
<%@page contentType="text/html; charset=utf-8" %><%--
--%><!DOCTYPE html>
<html>
 <head>
  <meta charset="utf-8">
  <title>サンプル</title>
 </head>
 <body>
  チェックされた項目は<br>
  <c:forEach items="${isbns}" var="isbn">
   <c:out value="${isbn}" />
  </c:forEach>
 </body>
</html>
//}

path属性で、モデルの値とタグを関連付けます。

実際に動作させ、出力されるHTMLは以下のようになります（見やすくするために改行を入れています）。

//list[037-html][出力されるHTML]{
<!DOCTYPE html>
<html>
 <head>
  <meta charset="utf-8">
  <title>サンプル</title>
 </head>
 <body>
  <form action="checkboxesRecv">
   <span><input id="selectedIsbn1" name="selectedIsbn" type="checkbox" value="123"/>
    <label for="selectedIsbn1">よく分かるSpring</label></span>
   <span><input id="selectedIsbn2" name="selectedIsbn" type="checkbox" value="456"
    checked="checked"/>
    <label for="selectedIsbn2">よく分かるJava</label></span>
   <span> <input id="selectedIsbn3" name="selectedIsbn" type="checkbox" value="789"/>
    <label for="selectedIsbn3">よく分かるSpring MVC</label></span>
     <input type="hidden" name="_selectedIsbn" value="on"/><br>
   <input type="submit" value="送信">
  </form>
 </body>
</html>
//}

label属性を指定していると、HTMLのlabel要素が出力されます。

==={038} form:radiobuttonタグ

@<b>{タグ【038】}

form:radiobuttonタグは、HTMLの<input type="radio">タグを生成します。

その要素の内、単純にHTMLの属性に置き換えられるものは、以下の属性です。cssClassやcssStyleはそれぞれclass、style属性に置き換えられます。

//table[038-form:radiobutton1][HTMLの属性]{
属性		説明
-------------------------------------------------------------
accesskey	HTML標準のaccesskey属性
cssClass	HTML標準のclass属性
cssStyle	HTML標準のsytle属性
dir			HTML標準のdir属性
disabled	HTML標準のdisabled属性
id			HTML標準のid属性
lang		HTML標準のlang属性
tabindex	HTML標準のtabindex
title		HTML標準のtitle属性
value		HTML標準のvalue属性
//}

その他、JavaScriptのDOMレベル0イベントとして以下の属性が用意されています。それぞれ同名の属性になります。

//table[038-form:raidobutton2][イベントハンドラの属性]{
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
//}

残りがSpring用の属性になります。

//table[038-form:radiobutton3][Springの属性]{
属性			説明
-------------------------------------------------------------
cssErrorClass	Validationのエラー時のclass属性
htmlEscape		HTMLのエスケープをするかどうか。デフォルトはtrue
label			HTMLのlabel要素を作成し、チェックボックスと関連付ける
path			関連付けるModelの名前
//}

使用するモデルです。ラジオボタンの初期値として利用します。

//list[038-C038Model.java][C038Model.java]{
package com.example.spring.controller.c038;

public class C038Model {
    private String tel;

    // setter、getterは省略
}
//}

サンプルのコントローラーです。

//list[038-C038Controller.java][C038Controller.java]{
package com.example.spring.controller.c038;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;

@Controller
@RequestMapping("/c038")
public class C038Controller {
    @RequestMapping("/radiobutton")
    public String radiobutton(Model model) {
        C038Model c038Model = new C038Model();
        c038Model.setTel("mobile");

        model.addAttribute("c038Model", c038Model);
        return "c038/radiobutton";
    }

    @RequestMapping("/radiobuttonRecv")
    public String radiobuttonRecv(@RequestParam String tel, Model model) {
        model.addAttribute("recvData", tel);
        return "c038/radiobuttonRecv";
    }
}
//}

コントローラーではformで利用する値をModelに格納しています。

カスタムタグを使用しているJSPです。

//list[038-radiobutton.jsp][radiobutton.jsp]{
<%@page contentType="text/html; charset=utf-8" %><%--
--%><!DOCTYPE html>
<html>
 <head>
  <meta charset="utf-8">
  <title>サンプル</title>
 </head>
 <body>
  <form action="radiobuttonRecv">
   <form:radiobutton path="c038Model.tel" label="固定電話" value="home" /><br>
   <form:radiobutton path="c038Model.tel" label="携帯電話" value="mobile" /><br>
   <form:radiobutton path="c038Model.tel" label="なし" value="nothing" /><br>
   <input type="submit" value="送信">
  </form>
 </body>
</html>
//}

受信するradiobuttonRecv.jspです。

//list[038-radiobuttonRecv.jsp][radiobuttonRecv.jsp]{
<%@page contentType="text/html; charset=utf-8" %><%--
--%><!DOCTYPE html>
<html>
 <head>
  <meta charset="utf-8">
  <title>サンプル</title>
 </head>
 <body>
受信データ: <c:out value="${recvData}" /><br>
 </body>
</html>
//}

path属性で、モデルの値とタグを関連付けます。

実際に動作させ、出力されるHTMLは以下のようになります（見やすくするために改行を入れています）。

//list[038-html][出力されるHTML]{
<!DOCTYPE html>
<html>
 <head>
  <meta charset="utf-8">
  <title>サンプル</title>
 </head>
 <body>
  <form action="radiobuttonRecv">
   <input id="tel1" name="tel" type="radio" value="home"/>
   <label for="tel1">固定電話</label><br>
   <input id="tel2" name="tel" type="radio" value="mobile" checked="checked"/>
   <label for="tel2">携帯電話</label><br>
   <input id="tel3" name="tel" type="radio" value="nothing"/>
   <label for="tel3">なし</label><br>
   <input type="submit" value="送信">
  </form>
 </body>
</html>
//}

label属性を指定していると、HTMLのlabel要素が出力されます。

==={039} form:radiobuttonsタグ

@<b>{タグ【039】}

form:radiobuttonsタグは、HTMLの<input type="radio">タグのまとまりを生成します。

その要素の内、単純にHTMLの属性に置き換えられるものは、以下の属性です。cssClassやcssStyleはそれぞれclass、style属性に置き換えられます。

//table[039-form:radiobuttons1][HTMLの属性]{
属性		説明
-------------------------------------------------------------
accesskey	HTML標準のaccesskey属性
cssClass	HTML標準のclass属性
cssStyle	HTML標準のsytle属性
dir			HTML標準のdir属性
disabled	HTML標準のdisabled属性
id			HTML標準のid属性
lang		HTML標準のlang属性
tabindex	HTML標準のtabindex
title		HTML標準のtitle属性
//}

その他、JavaScriptのDOMレベル0イベントとして以下の属性が用意されています。それぞれ同名の属性になります。

//table[039-form:radiobuttons2][イベントハンドラの属性]{
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
//}

残りがSpring用の属性になります。

//table[039-form:radiobuttons][Springの属性]{
属性			説明
-------------------------------------------------------------
cssErrorClass	Validationのエラー時のclass属性
delimiter		チェックボックスの間の区切り文字。デフォルトはなし
element			それぞれのradioボタンを囲む要素。デフォルトはspan
htmlEscape		HTMLのエスケープをするかどうか。デフォルトはtrue
itemLabel		labelを出力するitemsで指定したクラスのプロパティ名
items			radioボタンを作るための配列やMap
itemValue		valueを出力するitemsで指定したクラスのプロパティ名
path			関連付けるModelの名前
//}

実際の例を見ていきます。まずは、radioボタンの初期値を設定するモデルです。

//list[039-C039Form.java][C039Form.java]{
package com.example.spring.controller.c039;

public class C039Form {
    private String selectedIsbn;

    // getter、setterは省略
}
//}

書籍データを格納するモデルです。このクラスの一つのインスタンスが1つのラジオボタンに相当します。

//list[039-C039Model.java][C039Model.java]{
package com.example.spring.controller.c039;

public class C039Model {
    private String isbn;
    private String name;

    public C039Model(String isbn, String name) {
        this.isbn = isbn;
        this.name = name;
    }

    // setter、getterは省略
}
//}

サンプルのコントローラです。

//list[039-C039Controller.java][C039Controller.java]{
package com.example.spring.controller.c039;

import java.util.ArrayList;
import java.util.List;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;

@Controller
@RequestMapping("/c039")
public class C039Controller {
    @RequestMapping("/radiobuttons")
    public String radiobuttons(Model model) {
        List<C039Model> c039ModelList = new ArrayList<>();

        c039ModelList.add(new C039Model("123", "よく分かるSpring"));
        c039ModelList.add(new C039Model("456", "よく分かるJava"));
        c039ModelList.add(new C039Model("790", "よく分かるSpring MVC"));

        model.addAttribute("c039ModelList", c039ModelList);

        C039Form c039Form = new C039Form();
        c039Form.setSelectedIsbn("456");
        model.addAttribute("c039Form", c039Form);
        return "c039/radiobuttons";
    }

    @RequestMapping("/radiobuttonsRecv")
    public String radiobuttonsRecv(
            @RequestParam(required = false) String selectedIsbn, Model model) {
        model.addAttribute("isbn", selectedIsbn);
        return "c039/radiobuttonsRecv";
    }
}
//}

radiobuttonsメソッドではラジオボタンとして表示するためにBookクラスのオブジェクトのリストを作成しています。また、ラジオボタンの初期値として、C039FormクラスのselectedIsbnに選択状態とするラジオボタンのisbn（value）を指定します。

カスタムタグを使用しているJSPです。

//list[039-radiobuttons.jsp][radiobuttons.jsp]{
<%@page contentType="text/html; charset=utf-8" %><%--
--%><!DOCTYPE html>
<html>
 <head>
  <meta charset="utf-8">
  <title>サンプル</title>
 </head>
 <body>
  <form action="radiobuttonsRecv">
   <form:radiobuttons path="c039Form.selectedIsbn" items="${c039ModelList}"
    itemLabel="name" itemValue="isbn" delimiter=" " /><br>
   <input type="submit" value="送信">
  </form>
 </body>
</html>
//}

JSPではラジオボタンのリストをitems属性で指定します。itemLabelとitemValueでチェックボックスのラベルとvalueを取得するフィールド名を指定します。

受信するradiobuttonsRecv.jspです。

//list[039-radiobuttonsRecv.jsp][radiobuttonsRecv.jsp]{
<%@page contentType="text/html; charset=utf-8" %><%--
--%><!DOCTYPE html>
<html>
 <head>
  <meta charset="utf-8">
  <title>サンプル</title>
 </head>
 <body>
  チェックされた項目は<c:out value="${isbn}" />
 </body>
</html>
//}

path属性で、モデルの値とタグを関連付けます。

実際に動作させ、出力されるHTMLは以下のようになります（見やすくするために改行を入れています）。

//list[039-html][出力されるHTML]{
<!DOCTYPE html>
<html>
 <head>
  <meta charset="utf-8">
  <title>サンプル</title>
 </head>
 <body>
  <form action="radiobuttonsRecv">
   <span><input id="selectedIsbn1" name="selectedIsbn" type="radio" value="123"/>
    <label for="selectedIsbn1">よく分かるSpring</label></span>
   <span> <input id="selectedIsbn2" name="selectedIsbn" type="radio" value="456" 
    checked="checked"/>
    <label for="selectedIsbn2">よく分かるJava</label></span>
   <span> <input id="selectedIsbn3" name="selectedIsbn" type="radio" value="790"/>
    <label for="selectedIsbn3">よく分かるSpring MVC</label></span><br>
   <input type="submit" value="送信">
  </form>
 </body>
</html>
//}

label属性を指定していると、HTMLのlabel要素が出力されます。

==={040} form:selectタグ

@<b>{タグ【040】}

form:selectタグは、HTMLの<select>タグとその雇用そのoptionタグを生成します。

その要素の内、単純にHTMLの属性に置き換えられるものは、以下の属性です。cssClassやcssStyleはそれぞれclass、style属性に置き換えられます。

//table[040-form:select1][HTMLの属性]{
属性		説明
-------------------------------------------------------------
accesskey	HTML標準のaccesskey属性
cssClass	HTML標準のclass属性
cssStyle	HTML標準のsytle属性
dir			HTML標準のdir属性
disabled	HTML標準のdisabled属性
id			HTML標準のid属性
lang		HTML標準のlang属性
multiple	HTML標準のmultiple要素。trueかfalseを指定する
size		HTML標準のsize属性
tabindex	HTML標準のtabindex
title		HTML標準のtitle属性
//}

その他、JavaScriptのDOMレベル0イベントとして以下の属性が用意されています。それぞれ同名の属性になります。

//table[040-form:select2][イベントハンドラの属性]{
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
//}

残りがSpring用の属性になります。

//table[040-form:select3][Springの属性]{
属性			説明
-------------------------------------------------------------
cssErrorClass	Validationのエラー時のclass属性
delimiter		チェックボックスの間の区切り文字。デフォルトはなし
element			それぞれのradioボタンを囲む要素。デフォルトはspan
htmlEscape		HTMLのエスケープをするかどうか。デフォルトはtrue
itemLabel		labelを出力するitemsで指定したクラスのプロパティ名
items			radioボタンを作るための配列やMap
itemValue		valueを出力するitemsで指定したクラスのプロパティ名
path			関連付けるModelの名前
//}

実際の例を見ていきます。まずは選択されたの要素の初期値を設定するモデルです。

//list[040-C040Form.java][C040Form.java]{
package com.example.spring.controller.c040;

public class C040Form {
    private String selectedIsbn;

    // setter、getterは省略
}
//}

書籍データを格納するモデルです。このクラスの一つのインスタンスが1つのoption要素に相当します。

//list[040-C040Model.java][C040Model.java]{
package com.example.spring.controller.c040;

public class C040Model {
    private String isbn;
    private String name;

    public C040Model(String isbn, String name) {
        this.isbn = isbn;
        this.name = name;
    }

    // setter、getterは省略
}
//}

サンプルのコントローラーです。

//list[040-C040Controller.java][C040Controller.java]{
package com.example.spring.controller.c040;

import java.util.ArrayList;
import java.util.List;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestMapping;

@Controller
@RequestMapping("/c040")
public class C040Controller {
    @RequestMapping("/select")
    public String select(Model model) {
        List<C040Model> c040ModelList = new ArrayList<>();

        c040ModelList.add(new C040Model("123", "よく分かるSpring"));
        c040ModelList.add(new C040Model("456", "よく分かるJava"));
        c040ModelList.add(new C040Model("789", "よく分かるSpring MVC"));

        model.addAttribute("c040ModelList", c040ModelList);

        C040Form c040Form = new C040Form();
        c040Form.setSelectedIsbn("456");
        model.addAttribute("c040Form", c040Form);
        return "c040/select";
    }
}
//}

optionメソッドではラジオボタンとして表示するためにC040Modelクラスのオブジェクトのリストを作成しています。また、ラジオボタンの初期値として、C040FormクラスのselectedIsbnに選択状態とするisbn（value）を指定します。

カスタムタグを使用しているJSPです。

//list[040-select.jsp][select.jsp]{
<%@page contentType="text/html; charset=utf-8" %><%--
--%><!DOCTYPE html>
<html>
 <head>
  <meta charset="utf-8">
  <title>サンプル</title>
 </head>
 <body>
  <form action="selectRecv">
   <form:select path="c040Form.selectedIsbn" items="${c040ModelList}" itemLabel="name"
    itemValue="isbn" delimiter=" " /><br>
   <form:select path="c040Form.selectedIsbn" multiple="true" size="3"
    items="${c040ModelList}" itemLabel="name" itemValue="isbn" delimiter=" " /><br>
  </form>
 </body>
</html>
//}

JSPではラジオボタンのリストをitems属性で指定します。itemLabelとitemValueでチェックボックスのラベルとvalueを取得するフィールド名を指定します。

実際に動作させ、出力されるHTMLは以下のようになります（見やすくするために改行を入れています）。

//list[040-html][出力されるHTML]{
<!DOCTYPE html>
<html>
 <head>
  <meta charset="utf-8">
  <title>サンプル</title>
 </head>
 <body>
  <form action="selectRecv">
   <select id="selectedIsbn" name="selectedIsbn">
    <option value="123">よく分かるSpring</option>
    <option value="456" selected="selected">よく分かるJava</option>
    <option value="789">よく分かるSpring MVC</option>
   </select><br>
   <select id="selectedIsbn" name="selectedIsbn" multiple="multiple" size="3">
    <option value="123">よく分かるSpring</option>
    <option value="456" selected="selected">よく分かるJava</option>
    <option value="789">よく分かるSpring MVC</option>
   </select>
   <input type="hidden" name="_selectedIsbn" value="1"/><br>
  </form>
 </body>
</html>
//}

==={041} form:optionタグ

@<b>{タグ【041】}

form:optionタグは、HTMLの<input type="text">タグを生成します。

その要素の内、単純にHTMLの属性に置き換えられるものは、以下の属性です。cssClassやcssStyleはそれぞれclass、style属性に置き換えられます。

//table[041-form:option1][HTMLの属性]{
属性		説明
-------------------------------------------------------------
cssClass	HTML標準のclass属性
cssStyle	HTML標準のsytle属性
dir			HTML標準のdir属性
disabled	HTML標準のdisabled属性
id			HTML標準のid属性
lang		HTML標準のlang属性
tabindex	HTML標準のtabindex
title		HTML標準のtitle属性
value		HTML標準のvalue属性
//}

その他、JavaScriptのDOMレベル0イベントとして以下の属性が用意されています。それぞれ同名の属性になります。

//table[041-form:select2][イベントハンドラの属性]{
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
//}

残りがSpring用の属性になります。

//table[041-form:option3][Springの属性]{
属性			説明
-------------------------------------------------------------
cssErrorClass	Validationのエラー時のclass属性
htmlEscape		HTMLのエスケープをするかどうか。デフォルトはtrue
label			HTMLのlabel要素を作成し、チェックボックスと関連付ける
//}

コントローラで使用するモデルです。

//list[04-C041Model.java][C041Model.java]{
package com.example.spring.controller.c041;

public class C041Model {
    private String selectedIsbn;

    public String getSelectedIsbn() {
        return selectedIsbn;
    }

    public void setSelectedIsbn(String selectedIsbn) {
        this.selectedIsbn = selectedIsbn;
    }
}
//}

サンプルのコントローラです。

//list[041-C041Controller.java][C041Controller.java]{
package com.example.spring.controller.c041;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestMapping;

@Controller
@RequestMapping("/c041")
public class C041Controller {
    @RequestMapping("/option")
    public String option(Model model) {
        C041Model c041Model = new C041Model();
        c041Model.setSelectedIsbn("");
        model.addAttribute("c041Model", c041Model);
        return "c041/option";
    }
}
//}

コントローラではformで利用する値をModelに格納しています。

カスタムタグを使用しているJSPです。

//list[041-option.jsp][option.jsp]{
<%@page contentType="text/html; charset=utf-8" %><%--
--%><!DOCTYPE html>
<html>
 <head>
  <meta charset="utf-8">
  <title>サンプル</title>
 </head>
 <body>
  <form:select path="c041Model.selectedIsbn">
   <form:option value="123" label="よく分かるSpring"/>
   <form:option value="456" label="よく分かるJava"/>
   <form:option value="789" label="よく分かるSpring MVC"/>
  </form:select>
 </body>
</html>
//}

実際に動作させ、出力されるHTMLは以下のようになります（見やすくするために改行を入れています）。

//list[041-html][出力されるHTML]{
<!DOCTYPE html>
<html>
 <head>
  <meta charset="utf-8">
  <title>サンプル</title>
 </head>
 <body>
  <select id="selectedIsbn" name="selectedIsbn">
   <option value="123">よく分かるSpring</option>
   <option value="456">よく分かるJava</option>
   <option value="789">よく分かるSpring MVC</option>
  </select>
 </body>
</html>
//}

==={042} form:optionsタグ

@<b>{タグ【042】}

form:optionsタグは、HTMLの&lt;option&gt;タグを生成します。このタグは、form:selectタグの中に書く必要があります。

その要素の内、単純にHTMLの属性に置き換えられるものは、以下の属性です。cssClassやcssStyleはそれぞれclass、style属性に置き換えられます。

//table[042-form:options1][HTMLの属性]{
属性		説明
-------------------------------------------------------------
cssClass	HTML標準のclass属性
cssStyle	HTML標準のsytle属性
dir			HTML標準のdir属性
disabled	HTML標準のdisabled属性
id			HTML標準のid属性
lang		HTML標準のlang属性
tabindex	HTML標準のtabindex
title		HTML標準のtitle属性
//}

その他、JavaScriptのDOMレベル0イベントとして以下の属性が用意されています。それぞれ同名の属性になります。


//table[042-form:options2][イベントハンドラの属性]{
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
//}

残りがSpringの属性になります。

//table[042-form:options3][Springの属性]{
属性			説明
-------------------------------------------------------------
cssErrorClass	Validationのエラー時のclass属性
htmlEscape		HTMLのエスケープをするかどうか。デフォルトはtrue
itemLabel		labelを出力するitemsで指定したクラスのプロパティ名
items			radioボタンを作るための配列やMap
itemValue		valueを出力するitemsで指定したクラスのプロパティ名
//}

実際の例を見ていきます。まずは選択されたの要素の初期値を設定するモデルです。

//list[042-C042Form.java][C042Form.java]{
package com.example.spring.controller.c042;

public class C042Form {
    private String selectedIsbn;

    // setter、getterは省略
}
//}

書籍データを格納するモデルです。このクラスの一つのインスタンスが1つのoption要素に相当します。

//list[042-C042Model.java][C042Model.java]{
package com.example.spring.controller.c042;

public class C042Model {
    private String isbn;
    private String name;

    // setter、getterは省略
}
//}

サンプルのコントローラーです。

//list[042-C42Controller.java][C042Controller.java]{
package com.example.spring.controller.c042;

import java.util.ArrayList;
import java.util.List;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestMapping;

@Controller
@RequestMapping("/c042")
public class C042Controller {
    @RequestMapping("/options")
    public String options(Model model) {
        List<C042Model> c042ModelList = new ArrayList<>();

        c042ModelList.add(new C042Model("123", "よく分かるSpring"));
        c042ModelList.add(new C042Model("456", "よく分かるJava"));
        c042ModelList.add(new C042Model("789", "よく分かるSpring MVC"));

        model.addAttribute("c042ModelList", c042ModelList);

        C042Form c042Form = new C042Form();
        c042Form.setSelectedIsbn("");
        model.addAttribute("c042Form", c042Form);
        return "c042/options";
    }
}
//}

コントローラではformで利用する値をModelに格納しています。

カスタムタグを使用しているJSPです。

//list[042-options.jsp][options.jsp]{
<%@page contentType="text/html; charset=utf-8" %><%--
--%><!DOCTYPE html>
<html>
 <head>
  <meta charset="utf-8">
  <title>サンプル</title>
 </head>
 <body>
  <form:select path="c042Form.selectedIsbn">
   <form:options items="${c042ModelList}" itemLabel="name" itemValue="isbn" />
  </form:select>
 </body>
</html>
//}

実際に動作させ、出力されるHTMLは以下のようになります（見やすくするために改行を入れています）。

//list[042-html][出力されるHTML]{
<!DOCTYPE html>
<html>
 <head>
  <meta charset="utf-8">
  <title>サンプル</title>
 </head>
 <body>
  <select id="selectedIsbn" name="selectedIsbn">
   <option value="123">よく分かるSpring</option>
   <option value="456">よく分かるJava</option>
   <option value="789">よく分かるSpring MVC</option>
  </select>
 </body>
</html>
//}


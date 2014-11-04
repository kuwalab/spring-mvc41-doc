= 入力チェック

== 型チェック

==={011} 受け取る型のチェック

@<b>{タグ【011】}

今までパラメータはすべてStringで受けていたので、型変換のエラー等は発生していませんでした。ここでは、String型以外の型でパラメータを受け取りどのような動作になるかを確認していきます。

最初にパラメータを受けつ取るクラスを作成します。price変数をIntegerにしておきどのように動作するのかを確認します。

//list[011-C011Model.java][C011Model.java]{
package com.example.spring.controller.c011;

public class C011Model {
    private String name;
    private Integer price;

    // setter、getterは省略
}
//}

Controllerクラスです。ModelAttriubteでC011Modelのパラメータを受け取ります。また、C011Modelへのパラメータの割り当ての際のエラーを取得するため、C011の次の引数にBindingResultクラスを指定します。BIndingResultクラスは、バインドされるクラスの次の引数にないといけません。

//list[011-C011Controller.java][C011Controller.java]{
package com.example.spring.controller.c011;

import org.springframework.stereotype.Controller;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.RequestMapping;

@Controller
@RequestMapping("/c011")
public class C011Controller {
    @RequestMapping("/checkType")
    public String checkType(@ModelAttribute C011Model c011Model,
            BindingResult errors) {
        return "c011/checkType";
    }
}
//}

最後に表示用のJSPです。

//list[0cc-checkType.jsp][checkType.jsp]{
<%@page contentType="text/html; charset=utf-8" %><%--
--%><!DOCTYPE html>
<html>
 <head>
  <meta charset="utf-8">
  <title>サンプル</title>
 </head>
 <body>
 バインディングエラー <form:errors path="c011Model.*" /><br>
c011Model.nameの値は <c:out value="${c011Model.name}" /><br>
c011Model.priceの値は <c:out value="${c011Model.price}" /><br>
 </body>
</html>
//}

このプログラムで「/c011/checkType?name=書籍&price=文字列」というリクエストを投げると次の様な出力になります。

//cmd{
バインディングエラー Failed to convert property value of
type java.lang.String to required type java.lang.Integer
for property price; nested exception is java.lang.NumberFormatException: For
input string: "文字列"
c011Model.nameの値は 
c011Model.priceの値は 
//}

c011Model.priceには文字列のためバインディングができずnullが入っています。また、バインディング失敗のデフォルトのエラーメッセージが表示されます。

このままだと、非常にわかりにくいのでデフォルトのエラーメッセージを変更します。

まず、spring-context.xmlにメッセージソースの設定を追加します。

//emlist{
<bean id="messageSource"
 class="org.springframework.context.support.ReloadableResourceBundleMessageSource">
 <property name="basename" value="classpath:/messages" />
</bean>
//}

そして、指定した名前+「.properties」ファイルを作成します。今回は型変換のエラーのメッセージだけを記載します。

//emlist{
typeMismatch.java.lang.Integer=整数で入力してください。
//}

このメッセージは、@<href>{http://docs.spring.io/spring/docs/current/javadoc-api/org/springframework/validation/DefaultMessageCodesResolver.html, DefaultMessageCodesResolver}のJavaDocに記載のある通り、

 1. code + "." + object name + "." + field
 2. code + "." + field
 3. code + "." + field type
 4. code

の順でメッセージが解決されます。

この状態で先ほどと同じデータを送信すると上記のメッセージになります。

ここで、メッセージを以下のように変更します。

//emlist{
typeMismatch.java.lang.Integer={0}は整数で入力してください。
//}

ここで、また先程のリクエストを送信すると今回は{0}の部分がフィールド名になり、

//emlist{
priceは整数で入力してください。
//}

というメッセージにあります。このpriceの部分はフィールド名に対応していて、この名前も置換が可能です。

メッセージソースに、フィールド名の値をキーとして登録します。

//emlist{
price=価格
//}

そうすることで、最終的には以下のメッセージになります。

//cmd{
価格は整数で入力してください。
//}

確認用のテストケースは次のとおりです。

//list[011-C011ControllerTest.java][C011ControllerTest.java]{
package com.example.spring.controller.c011;

import static org.hamcrest.CoreMatchers.*;
import static org.junit.Assert.*;
import static org.springframework.test.web.servlet.request.MockMvcRequestBuilders.*;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.*;
import static org.springframework.test.web.servlet.setup.MockMvcBuilders.*;

import java.util.List;
import java.util.Map;

import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.support.DefaultMessageSourceResolvable;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit4.SpringJUnit4ClassRunner;
import org.springframework.test.context.web.WebAppConfiguration;
import org.springframework.test.web.servlet.MockMvc;
import org.springframework.test.web.servlet.MvcResult;
import org.springframework.validation.BindingResult;
import org.springframework.validation.FieldError;
import org.springframework.web.context.WebApplicationContext;
import org.springframework.web.servlet.ModelAndView;

@RunWith(SpringJUnit4ClassRunner.class)
@WebAppConfiguration
@ContextConfiguration(locations = {
    "file:src/main/webapp/WEB-INF/spring/spring-context.xml" })
public class C011ControllerTest {
    @Autowired
    private WebApplicationContext wac;

    private MockMvc mockMvc;

    @Before
    public void setup() {
        mockMvc = webAppContextSetup(wac).build();
    }

    @Test
    public void checkTypeへのGET_priceが1000() throws Exception {
        MvcResult mvcResult = mockMvc
                .perform(get("/c011/checkType").param("price", "1000"))
                .andExpect(status().isOk())
                .andExpect(view().name("c011/checkType"))
                .andExpect(model().hasNoErrors())
                .andExpect(model().attributeExists("c011Model")).andReturn();

        Map<String, Object> model = mvcResult.getModelAndView().getModel();
        Object c011ModelObject = model.get("c011Model");
        assertThat(c011ModelObject, is(notNullValue()));
        assertThat(c011ModelObject, is(instanceOf(C011Model.class)));
        C011Model c011Model = (C011Model) c011ModelObject;
        assertThat(c011Model.getPrice(), is(1000));
    }

    @Test
    public void checkTypeへのGET_priceがabc() throws Exception {
        MvcResult mvcResult = mockMvc
                .perform(get("/c011/checkType").param("price", "abc"))
                .andExpect(status().isOk())
                .andExpect(view().name("c011/checkType"))
                .andExpect(model().hasErrors())
                .andExpect(model().errorCount(1))
                .andExpect(
                        model().attributeHasFieldErrors("c011Model", "price"))
                .andExpect(model().attributeExists("c011Model")).andReturn();

        // パラメータのチェック
        ModelAndView mav = mvcResult.getModelAndView();
        Map<String, Object> model = mav.getModel();
        Object c011ModelObject = model.get("c011Model");
        assertThat(c011ModelObject, is(notNullValue()));
        assertThat(c011ModelObject, is(instanceOf(C011Model.class)));
        C011Model c011Model = (C011Model) c011ModelObject;
        assertThat(c011Model.getPrice(), is(nullValue()));

        // エラーメッセージのチェック
        Object object = mav.getModel().get(
                "org.springframework.validation.BindingResult.c011Model");
        assertThat(object, is(not(nullValue())));
        assertThat(object, is(instanceOf(BindingResult.class)));
        BindingResult bindingResult = (BindingResult) object;

        // エラーのあるフィールドの取得
        List<FieldError> list = bindingResult.getFieldErrors("price");
        assertThat(list, is(not(nullValue())));
        assertThat(list.size(), is(1));

        // 詳細なエラーチェック
        FieldError fieldError = list.get(0);
        assertThat(fieldError.getCode(), is("typeMismatch"));

        // エラーメッセージのパラメータ
        Object[] args = fieldError.getArguments();
        assertThat(args.length, is(1));
        assertThat(args[0],
                is(instanceOf(DefaultMessageSourceResolvable.class)));
        DefaultMessageSourceResolvable dmr = (DefaultMessageSourceResolvable) args[0];
        assertThat(dmr.getCode(), is("price"));
    }
}
//}

== JSR349によるvalidation

==={012} Validatorでnullチェック

@<b>{タグ【012】}

Springは標準でBean Validationをサポートしており、Spring 4.0からはJSR-349のBean Validation 1.1をサポートしています。今回はSpringでBean Validationを使うための設定と、nullチェックのサンプルを紹介します。

まず、MavenでBean Validation関連のライブラリーを追加します。

//list[012-pom.xml][pom.xml]{
<dependency>
 <groupId>javax.el</groupId>
 <artifactId>javax.el-api</artifactId>
 <version>3.0.0</version>
 <scope>provided</scope>
</dependency>
<dependency>
 <groupId>javax.validation</groupId>
 <artifactId>validation-api</artifactId>
 <version>1.1.0.Final</version>
</dependency>
<dependency>
 <groupId>org.hibernate</groupId>
 <artifactId>hibernate-validator</artifactId>
 <version>5.1.1.Final</version>
</dependency>
//}

Bean Validation 1.1本体と、参照実装のHibernate 5.1、また、Bean Validation 1.1からは内部でEL 3.0を使用するためELのライブラリーを追加しています。

ついでSpring MVCの設定のWEB-INF/spring/spring-context.xmlを編集します。それなりの量が変わるため全体を再掲しています。

//list[012-spring-context.xml][spring-context.xml]{
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
 xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
 xmlns:context="http://www.springframework.org/schema/context"
 xmlns:mvc="http://www.springframework.org/schema/mvc"
 xsi:schemaLocation="http://www.springframework.org/schema/beans
http://www.springframework.org/schema/beans/spring-beans-4.1.xsd
http://www.springframework.org/schema/context
http://www.springframework.org/schema/context/spring-context-4.1.xsd
http://www.springframework.org/schema/mvc
http://www.springframework.org/schema/mvc/spring-mvc-4.1.xsd">
 <mvc:annotation-driven validator="validator" />
 <context:component-scan base-package="com.example.spring">
  <context:exclude-filter type="regex"
   expression="com\.example\.spring\.controller\..*Test" />
 </context:component-scan>
 <bean
  class="org.springframework.web.servlet.view.InternalResourceViewResolver">
  <property name="prefix" value="/WEB-INF/jsp/" />
  <property name="suffix" value=".jsp" />
 </bean>
 <bean id="messageSource"
  class="org.springframework.context.support.ReloadableResourceBundleMessageSource">
  <property name="basename" value="classpath:/messages" />
 </bean>
 <bean id="validator"
  class="org.springframework.validation.beanvalidation.LocalValidatorFactoryBean">
  <property name="validationMessageSource" ref="messageSource" />
 </bean>
</beans>
//}

messageSourceを定義し、そのソースをvalidatorに関連付けます。そのvalidatorを<mvc:annotation-driven>のvalidator属性に設定し、Validatorの設定は完了となります。

メッセージリソースは、Hibernateに付属のプロパティファイルをそのまま利用します。

//list[012-messages.properties][messages.properties]{
javax.validation.constraints.AssertFalse.message = must be false
javax.validation.constraints.AssertTrue.message = must be true
javax.validation.constraints.DecimalMax.message =
    must be less than ${inclusive == true ? 'or equal to ' : ''}{value}
javax.validation.constraints.DecimalMin.message =
    must be greater than ${inclusive == true ? 'or equal to ' : ''}{value}
javax.validation.constraints.Digits.message =
    numeric value out of bounds (<{integer} digits>.<{fraction} digits> expected)
javax.validation.constraints.Future.message = must be in the future
javax.validation.constraints.Max.message = must be less than or equal to {value}
javax.validation.constraints.Min.message = must be greater than or equal to {value}
javax.validation.constraints.NotNull.message = may not be null
javax.validation.constraints.Null.message = must be null
javax.validation.constraints.Past.message = must be in the past
javax.validation.constraints.Pattern.message = must match "{regexp}"
javax.validation.constraints.Size.message = size must be between {min} and {max}

org.hibernate.validator.constraints.CreditCardNumber.message =
    invalid credit card number
org.hibernate.validator.constraints.EAN.message = invalid {type} barcode
org.hibernate.validator.constraints.Email.message =
    not a well-formed email address
org.hibernate.validator.constraints.Length.message =
    length must be between {min} and {max}
org.hibernate.validator.constraints.LuhnCheck.message =
    The check digit for ${value} is invalid, Luhn Modulo 10 checksum failed
org.hibernate.validator.constraints.Mod10Check.message =
    The check digit for ${value} is invalid, Modulo 10 checksum failed
org.hibernate.validator.constraints.Mod11Check.message =
    The check digit for ${value} is invalid, Modulo 11 checksum failed
org.hibernate.validator.constraints.ModCheck.message =
    The check digit for ${value} is invalid, ${modType} checksum failed
org.hibernate.validator.constraints.NotBlank.message = may not be empty
org.hibernate.validator.constraints.NotEmpty.message = may not be empty
org.hibernate.validator.constraints.ParametersScriptAssert.message =
    script expression "{script}" didn't evaluate to true
org.hibernate.validator.constraints.Range.message = must be between {min} and {max}
org.hibernate.validator.constraints.SafeHtml.message = may have unsafe html content
org.hibernate.validator.constraints.ScriptAssert.message =
    script expression "{script}" didn't evaluate to true
org.hibernate.validator.constraints.URL.message = must be a valid URL

org.hibernate.validator.constraints.br.CNPJ.message =
    invalid Brazilian corporate taxpayer registry number (CNPJ)
org.hibernate.validator.constraints.br.CPF.message =
    invalid Brazilian individual taxpayer registry number (CPF)
org.hibernate.validator.constraints.br.TituloEleitoral.message =
    invalid Brazilian Voter ID card number
//}

このままだと英語だけなので、必要な物から日本語にしていきます。日本語のメッセージリソースは、messages_ja.propertiesというファイル名にして以下の内容にしておきます。

//list[012-mesages.properties][messages.properties]{
javax.validation.constraints.NotNull.message = 入力は必須です

typeMismatch.java.lang.Integer={0}は整数で入力してください。
price=価格
//}

次にvalidatorを動作させるためのControllerを作成します。

//list[012-C012Controller.java][C012Controller.java]{
package com.example.spring.controller.c012;

import javax.validation.Valid;

import org.springframework.stereotype.Controller;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;

@Controller
@RequestMapping("/c012")
public class C012Controller {
    @RequestMapping("/bookForm")
    public String bookForm() {
        return "c012/bookForm";
    }

    @RequestMapping(value = "/bookRecv", method = RequestMethod.POST)
    public String bookRecv(@Valid @ModelAttribute C012Model c012Model,
            BindingResult errors) {
        if (errors.hasErrors()) {
            return "c012/bookForm";
        }
        return "c012/bookRecv";
    }
}
//}

コントローラで重要なのは、データを受信するbookRecvメソッドになります。bookRecvメソッドではデータを受け取るBookクラスに@Validアノテーションがついています。@Validアノテーションを付けることでBean Validationが動作するようになります。また、Bean Validationの検証結果は、次の引数のBindingResultの中に格納されます。

メソッドの中で、BindingResult#hasErrorsメソッドでエラーが有るか確認し、エラーがある場合には入力画面に戻るようにしています。

次に、C012Modelクラスの定義を確認します。

//list[012-C012Model.java][C012Model.java]{
package com.example.spring.controller.c012;

import javax.validation.constraints.NotNull;

public class C012Model {
    @NotNull
    private String name;
    @NotNull
    private Integer price;

    // setter、getterは省略
}
//}

C012Modelクラスの各フィールドには@NotNullアノテーションを付けています。このアノテーションを付けることで@Validの付いたコントローラで自動的にValidationが行われます。@NotNullアノテーションをつけているとフィールドがnullの場合に検証エラーとなります。

次にJSPを確認していきます。まずデータ送信をするためのフォームの画面（bookForm.jsp）です。

//list[012-bookForm.jsp][bookForm.jsp]{
<%@page contentType="text/html; charset=utf-8" %><%--
--%><!DOCTYPE html>
<html>
 <head>
  <meta charset="utf-8">
  <title>サンプル</title>
 </head>
 <body>
  <form action="bookRecv" method="post">
   書名: <input type="text" name="name" size="20">
    <form:errors path="c012Model.name" /><br>
   価格: <input type="text" name="price" size="20">
    <form:errors path="c012Model.price" /><br>
   <input type="submit" value="送信">
  </form>
 </body>
</html>
//}

入力画面では、入力フォームの後ろにエラー表示のカスタムタグをつけています。pathにはモデルオブジェクト（c012Model）のフィールド名を指定します。こうすることで、そのフィールドで発生したエラーがカスタムタグの場所に表示されます。

入力された結果の確認用のJSP（bookRecv.jsp）です。

//list[012-bookRecv.jsp][bookRecv.jsp]{
<%@page contentType="text/html; charset=utf-8" %><%--
--%><!DOCTYPE html>
<html>
 <head>
  <meta charset="utf-8">
  <title>サンプル</title>
 </head>
 <body>
c012Model.nameの値は <c:out value="${c012Model.name}" /><br>
c012Model.priceの値は <c:out value="${c012Model.price}" /><br>
 </body>
</html>
//}

ここまでで実際にエラーを検証できる環境が整いましたので、実際にエラーを発生させてみます。フォームに何も入力せずに送信ボタンを押すと価格のみエラーとなります。これは、受け取るフィールドの型の違いのために起こります。書名はString型のためフォームから送られてくる空文字列（""）を受け取るためnullにはなりません。対してpriceは空文字列はInteger型のため空文字列は受け取れずnullになります。そのため、priceのみ@NotNullでエラーとなります。

空文字のチェックのためにはBean Validation標準のアノテーションではなく、HibernateのValiationを使うとできます。この辺りは次回以降に解説していきます。

確認用のテストケースは次のとおりです。

//list[012-C012ControllerTest.java][C012ControllerTest.java]{
package com.example.spring.controller.c012;

import static org.hamcrest.CoreMatchers.*;
import static org.junit.Assert.*;
import static org.springframework.test.web.servlet.request.MockMvcRequestBuilders.*;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.*;
import static org.springframework.test.web.servlet.setup.MockMvcBuilders.*;

import java.util.List;
import java.util.Map;

import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.support.DefaultMessageSourceResolvable;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit4.SpringJUnit4ClassRunner;
import org.springframework.test.context.web.WebAppConfiguration;
import org.springframework.test.web.servlet.MockMvc;
import org.springframework.test.web.servlet.MvcResult;
import org.springframework.validation.BindingResult;
import org.springframework.validation.FieldError;
import org.springframework.web.context.WebApplicationContext;
import org.springframework.web.servlet.ModelAndView;

@RunWith(SpringJUnit4ClassRunner.class)
@WebAppConfiguration
@ContextConfiguration(locations = {
    "file:src/main/webapp/WEB-INF/spring/spring-context.xml" })
public class C012ControllerTest {
    @Autowired
    private WebApplicationContext wac;

    private MockMvc mockMvc;

    @Before
    public void setup() {
        mockMvc = webAppContextSetup(wac).build();
    }

    @Test
    public void bookFormへのGET() throws Exception {
        mockMvc.perform(get("/c012/bookForm")).andExpect(status().isOk())
                .andExpect(view().name("c012/bookForm"))
                .andExpect(model().hasNoErrors());
    }

    @Test
    public void bookRecvへのPOST_NOT_NULL() throws Exception {
        mockMvc.perform(
                post("/c012/bookRecv").param("name", "よくわかるSpring").param(
                        "price", "1000")).andExpect(status().isOk())
                .andExpect(view().name("c012/bookRecv"))
                .andExpect(model().hasNoErrors());
    }

    @Test
    public void bookRecvへのPOST_nameがnull() throws Exception {
        MvcResult mvcResult = mockMvc
                .perform(post("/c012/bookRecv").param("price", "1000"))
                .andExpect(status().isOk())
                .andExpect(view().name("c012/bookForm"))
                .andExpect(model().hasErrors())
                .andExpect(model().errorCount(1))
                .andExpect(model().attributeHasFieldErrors("c012Model", "name"))
                .andExpect(model().attributeExists("c012Model")).andReturn();

        // パラメータのチェック
        ModelAndView mav = mvcResult.getModelAndView();
        Map<String, Object> model = mav.getModel();
        Object c012ModelObject = model.get("c012Model");
        assertThat(c012ModelObject, is(notNullValue()));
        assertThat(c012ModelObject, is(instanceOf(C012Model.class)));
        C012Model c012Model = (C012Model) c012ModelObject;
        assertThat(c012Model.getName(), is(nullValue()));

        // エラーメッセージのチェック
        Object object = mav.getModel().get(
                "org.springframework.validation.BindingResult.c012Model");
        assertThat(object, is(not(nullValue())));
        assertThat(object, is(instanceOf(BindingResult.class)));
        BindingResult bindingResult = (BindingResult) object;

        checkField(bindingResult, "name", "NotNull");
    }

    @Test
    public void bookRecvへのPOST_nameとpriceがnull() throws Exception {
        MvcResult mvcResult = mockMvc
                .perform(post("/c012/bookRecv"))
                .andExpect(status().isOk())
                .andExpect(view().name("c012/bookForm"))
                .andExpect(model().hasErrors())
                .andExpect(model().errorCount(2))
                .andExpect(model().attributeHasFieldErrors("c012Model", "name"))
                .andExpect(
                        model().attributeHasFieldErrors("c012Model", "price"))
                .andExpect(model().attributeExists("c012Model")).andReturn();

        // パラメータのチェック
        ModelAndView mav = mvcResult.getModelAndView();
        Map<String, Object> model = mav.getModel();
        Object c012ModelObject = model.get("c012Model");
        assertThat(c012ModelObject, is(notNullValue()));
        assertThat(c012ModelObject, is(instanceOf(C012Model.class)));
        C012Model c012Model = (C012Model) c012ModelObject;
        assertThat(c012Model.getName(), is(nullValue()));

        // エラーメッセージのチェック
        Object object = mav.getModel().get(
                "org.springframework.validation.BindingResult.c012Model");
        assertThat(object, is(not(nullValue())));
        assertThat(object, is(instanceOf(BindingResult.class)));
        BindingResult bindingResult = (BindingResult) object;

        checkField(bindingResult, "name", "NotNull");
        checkField(bindingResult, "price", "NotNull");
    }

    private void checkField(BindingResult bindingResult, String fieldName,
            String errorCode) {
        // エラーのあるフィールドの取得
        List<FieldError> list = bindingResult.getFieldErrors(fieldName);
        assertThat(list, is(not(nullValue())));
        assertThat(list.size(), is(1));

        // 詳細なエラーチェック
        FieldError fieldError = list.get(0);
        assertThat(fieldError.getCode(), is(errorCode));

        // エラーメッセージのパラメータ
        Object[] args = fieldError.getArguments();
        assertThat(args.length, is(1));
        assertThat(args[0],
                is(instanceOf(DefaultMessageSourceResolvable.class)));
        DefaultMessageSourceResolvable dmr = (DefaultMessageSourceResolvable) args[0];
        assertThat(dmr.getCode(), is(fieldName));
    }
}
//}


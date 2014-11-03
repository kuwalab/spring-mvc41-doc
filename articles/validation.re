= 入力チェック

== 型チェック

==={011} 受け取る方のチェック

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


<?php require("../../resources/tutHead.inc"); ?>

<!-- tutorials start with a "Getting Started" block -->
<h3>Getting Started</h3>
<p>Yes, from Dojo 1.7 onwards, it has fundamentally changed.  While generally backwards compatible, items like the build system, modules and even the basics of how you use Dojo have changed.  New functionality like <code>dojo/on</code> refuses to look back and isn't even available in a "legacy" fashion.  If you have used Dojo before, it is truly unsettling waking up to a totally different place.</p>
<p>During this tutorial I will try to explain some of the concepts that have been introduced in Dojo in 1.7 and beyond that are part of the foundation for 2.0.  I will refer to these as "legacy" and "modern" Dojo.  I will do my best to explain how things and have changed and touch on why.  On thing you have to understand though is that the changes to Dojo weren't to frustrate you and make your life more difficult, although that may have been the result.  They were done after careful consideration (and much debate and testing) to ensure that Dojo and associated packages will be an excellent foundation going forward for JavaScript development.</p>

<h3>Hello New World</h3>

<p>One of the core concepts of "modern" Dojo is that things in the global namespace are bad.  There are numerous reasons for this, but in a complex web application, the global namespace can easily become polluted with all manner of code, especially when a lot of organisations use multiple JavaScript frameworks.  I won't even mention the nefarious things that can happen from a security standpoint with people intentionally modifying the global namespace.  This means in "modern" Dojo, if you are about to access something in the global namespace <strong>STOP</strong> because you are doing something wrong.  While for backwards compatibility reasons the vast majority of the toolkit for the moment scopes itself globally, it shouldn't be used for new development.</p>

<div class="proTip">If you find yourself typing <code>dojo.*</code> or <code>dijit.*</code> or <code>dojox.*</code>, something isn't right.</div>
<br />

<p>This does mean though for developer who are used to "legacy" Dojo, just including <code>dojo.js</code> and getting a core of functionality and the requiring in a few other modules and just typing <code>dojo.something</code> to your heart's content is gone (or really should be, because while it will likely work until 2.0, it is a BAD BAD thing).</p>
<p>Again, repeat after me "the global namespace is bad, the global namespace is bad, I will not use the global namespace, I will not use the global namespace".</p>
<p>Another core concept is that synchronous operations are slow and asynchronous ones are usually faster.  "Legacy" Dojo already had a fairly strong pedigree in asynchronous JavaScript code with the concept of <code>dojo.Deferred</code>, but in "modern" Dojo, it is best to think of everything operating asynchronously.</p>
<p>To strengthen the modularity of Dojo and leverage the concepts above, in 1.7 Dojo adopted the CommonJS module definition called Asynchronous Module Definition (AMD).  This meant a fundamental re-write of the Dojo module loader which is usually exposed through the <code>require()</code> and <code>define()</code> functions.  You can find full documentation of the <a href="/reference-guide/loader">loader in the reference guide</a>.

<p>Let's take for example something we would have done in "legacy":</p>
<pre class="brush:js;">
  dojo.ready(function(){
    dojo.byId("helloworld").innerHTML = "Hello World!";
  });
</pre>

<p>Now let's look at the modern version of this:</p>
<pre class="brush:js;">
  require(["dojo/dom", "dojo/domReady!"], function(dom){
    dom.byId("helloworld").innerHTML = "Hello New World!";
  });
</pre>
<a class="demoBtn demo" href="demo/helloworld.html">View Demo</a>

<p>Welcome, to the brave new world.  The foundation for "modern" Dojo is the <code>require()</code> function.  It creates a closure of JavaScript code and provides it with the modules it needs to do the job as return variables passed as arguments to the function.  Typically, the first argument is an array of module IDs (MIDs) and the second is the function.  Within the closure of the <code>require()</code>, we reference the modules based on the variable name we declared in the argument.  While we could call a module anything, there are some common conventions that are used and are usually noted in the Reference Guide.</p>
<p>The loader, just like the legacy one, does all the heavy lifting of finding the module, loading it and managing the loaded modules.</p>
<p>The sharped eyed among you will notice that there is a "module" in the requirement array that doesn't have a return variable, called <code>dojo/domReady!</code>.  This is actually a loader "plugin" that is used to control the behaviour of the loader.  This one ensures that the loader waits until the DOM structure for the page is ready.  In an async world, it isn't a bright idea to assume that your DOM structure if there if you want to manipulate it, so if you are going to be doing something with the DOM in your code, make sure you include this plugin.  Since we don't use the plugin in the code, it is the standard convention to put it at the end of the array and not provide a return variable for it.</p>
<div class="proTip">For now there is only the <code>dojo/domReady!</code> plugin, but that may not be sufficient for your code to work properly (as there are other things, like some of the a11y feature detection, that may not have run).  So, using <code>dojo/ready</code> when using things like the <code>dojo/parser</code> and Dijits is wise.</div>
<br />
<p>You can also get a reference to a module with <code>require()</code> after that module has already loaded, by just supplying the MID as a single string argument.  This won't load the module and will throw an error if it isn't already loaded.  You won't see this coding style in the Dojo Toolkit, because we like to manage all of our dependencies centrally in the code.  But if you choose to use this alternative syntax it would something like this:</p>
<pre class="brush:js;">
  require(["dojo/dom"], function(){
    // some code
    var dom = require("dojo/dom");
    // some more code
  });
</pre>

<div class="proTip">The other core function in AMD is <code>define()</code> which is usually used for defining modules.  See the <a href="../modules/">Defining Modules</a> tutorial for more information on how to use <code>define()</code></div>

<h3>Dojo Base and Core</h3>
<p>In the "legacy" world, there was quite a bit of functionality in the base <code>dojo.js</code> and in fact it is still there until at least Dojo 2.0, but if you want to make sure your code is easier to migrate as well as make sure your code does what you anticipate, you should stop using <code>dojo.*</code>.  This does mean you might not know where certain parts of the namespace are now.</p>
<p>In addition, Dojo is embracing EcmaScript 5 Specification, and where possible, deprecating parts of Dojo the emulated ES5 functionality and "shimming" where appropriate in order to bring ES5 functionality to non-modern browsers.  This does mean the "Dojo-way" in some situations is to not use Dojo at all.</p>
<p>While the Reference Guide has been updated to tell you where functionality is located now, there is a specific document that covers off where the <a href="http://livedocs.dojotoolkit.org/releasenotes/migration-2.0#basic-functions">basic functions</a> are now located.</p>

<p>Once you get outside of the Dojo Base and Core, almost everything else would work like the following.  Where you would have done a <code>dojo.require()</code>:</p>
<pre class="brush:js;">
  dojo.require("dojo.string");
  
  dojo.byId("someNode").innerHTML = dojo.string.trim("  I Like Trim Strings ");
</pre>

<p>You would now do a <code>require()</code>:</p>
<pre class="brush:js;">
  require(["dojo/dom", "dojo/string", "dojo/domReady!"], function(dom, string){
    dom.byId("someNode").innerHTML = string.trim("  I Like Trim Strings ");
  });
</pre>
<a class="demoBtn demo" href="demo/string.html">View Demo</a>

<h3>Events and Advice</h3>
<p>While <code>dojo.connect()</code> and <code>dojo.disconnect()</code> have been moved into the <code>dojo/_base/connect</code> module, "modern" Dojo should follow the pattern of using <code>dojo/on</code> for event handling and <code>dojo/aspect</code> for method advice.  There is a more full tutorial on <a href="../events/">Events</a> available, but we will cover some of the differences here.</p>
<p>In "legacy" Dojo, there was no clear distinction between Events and Advice for Join Points and <code>dojo.connect()</code> was used to deal with both.  Events are things the occur in relationship to an object, like for example a "click" event.  <code>dojo/on</code> deals seamlessly with native DOM events and those emitted by Dojo objects or widgets.  While advice is a concept that is part of aspect oriented programming (AOP) that add additional behaviour to a join point (or method).  While many parts of Dojo mostly followed AOP the <code>dojo/aspect</code> module provides a centralised mechanism to manifest this.</p>

<p>In "legacy" Dojo, we might have accomplished handling of a button <code>onclick</code> event a couple of different ways:</p>
<pre class="brush:js; html-script:true;">
  &lt;script&gt;
    dojo.require("dijit.form.Button");
    
    myOnClick = function(evt){
      console.log("I was clicked");
    };
    
    dojo.connect(dojo.byId("button3"), "onclick", myOnClick);
  &lt;/script&gt;
  &lt;body&gt;
    &lt;div&gt;
      &lt;button id="button1" type="button" onclick="myOnClick"&gt;Button1&lt;/button&gt;
      &lt;button id="button2" data-dojo-type="dijit.form.Button" type="button" 
        data-dojo-props="onClick: myOnClick"&gt;Button2&lt;/button&gt;
      &lt;button id="button3" type="button"&gt;Button3&lt;/button&gt;
      &lt;button id="button4" data-dojo-type="dijit.form.Button" type="button"&gt;
        &lt;span&gt;Button4&lt;/span&gt;
        &lt;script type="dojo/connect" data-dojo-event="onClick"&gt;
          console.log("I was clicked");
        &lt;/script&gt;
    &lt;/div&gt;
  &lt;/body&gt;
</pre>

<p>In "modern" Dojo, only using <code>dojo/on</code>, you can specify your code, both programatically and declaratively, as well as not worry about if it is the DOM event or the Dijit/widget event you are dealing with:</p>
<pre class="brush:js; html-script:true;">
  &lt;script&gt;
    require(["dojo/dom", "dojo/on", "dojo/parser", "dojo/ready", "dijit/registry", "dijit/form/Button"], 
    function(dom, on, parser, ready, registry){
      var myClick = function(evt){
        console.log("I was clicked");
      };

      ready(function(){
        parser.parse();

        on(dom.byId("button1"), "click", myClick);
        on(registry.byId("button2"), "click", myClick);
      });
    });
  &lt;/script&gt;
  &lt;body&gt;
    &lt;div&gt;
      &lt;button id="button1" type="button"&gt;Button1&lt;/button&gt;
      &lt;button id="button2" data-dojo-type="dijit.form.Button" type="button"&gt;Button2&lt;/button&gt;
      &lt;button id="button3" data-dojo-type="dijit.form.Button" type="button"&gt;
        &lt;div&gt;Button4&lt;/div&gt;
        &lt;script type="dojo/on" data-dojo-event="click"&gt;
          console.log("I was clicked");
        &lt;/script&gt;
      &lt;/button&gt;
    &lt;/div&gt;
  &lt;/body&gt;
</pre>
<a class="demoBtn demo" href="demo/button.html">View Demo</a>

<div class="proTip">Notice how <code>dijit.byId</code> isn't used.  In "modern" Dojo, the <code>dijit/registry</code> is used for widgets and <code>registry.byId()</code> retrieves a reference to the widget.  Also, notice how <code>dojo/on</code> handles both the DOM node and widget events in the same way.</div>
<br />
<div class="proTip">For declarative markup, you should make sure you require the necessary modules before invoking the <code>parser.parse()</code>, but the invocation doesn't have to sit within the closure where the require is done as the <code>parser</code> will obtain the necessary constructors from the loader itself.  This explains why we don't have to return the <code>dijit/form/Button</code> module as a return variable of the <code>require()</code>.</div>
<br />
<p>Adding functionality to methods in a "legacy" way you might have done something like:</p>
<pre class="brush:js;">
  var callback = function(){
    // ...
  };
  var handle = dojo.connect(myInstance, "execute", callback);
  // ...
  dojo.disconnect(handle);
</pre>

<p>In "modern" Dojo, the <code>dojo/aspect</code> module allows you to get advice from a method and add behaviour "before", "after" or "around" another method.  Typically, if you were converting a <code>dojo.connect()</code> you would replace it with an <code>aspect.after()</code> which would look something like this:</p>
<pre class="brush:js;">
  require(["dojo/aspect"], function(aspect){
    var callback = function(){
      // ...
    };
    var handle = aspect.after(myInstance, "execute", callback);
    // ...
    handle.remove();
  });
</pre>

<div class="proTip">Check out the reference guide for <a href="/reference-guide/dojo/aspect.html"><code>dojo/aspect</code></a> for more details as well as <a href="http://davidwalsh.name/dojo-aspect">David Walsh's blog on <code>dojo/aspect</code></a>.</div>

<h3>Topics</h3>

<p>Another area that has undergone a bit of a revision is the "publish/subscribe" functionality in Dojo.  This has been modularized under the <code>dojo/topic</code> module and improved.</p>

<p>For example, the "legacy" way of doing this would be something like:</p>
<pre class="brush:js;">
  // To publish a topic
  dojo.publish("some/topic", [1, 2, 3]);
  
  // To subscribe to a topic
  var handle = dojo.subscribe("some/topic", context, callback);
  
  // And to unsubscribe to a topic
  dojo.unsubscribe(handle);
</pre>

<p>In "modern" Dojo, you would leverage the <code>dojo/topic</code> module and do something like:</p>
<pre class="brush:js;">
  require(["dojo/topic"], function(topic){
    // To publish a topic
    topic.publish("some/topic", 1, 2, 3);
    
    // To subscribe to a topic
    var handle = topic.subscribe("some/topic", function(arg1, arg2, arg3){
      // ...
    });
    
    // To unsubscribe from a topic
    handle.remove();
  });
</pre>

<div class="proTip">Check out the reference guide for <a href="/reference-guide/dojo/topic.html"><code>dojo/topic</code></a> for more details.</div>
<br />
<div class="proTip">Notice how the publish arguments are not an array anymore and are simply passed on the publish.</div>

<h3>Promises</h3>
<p>One of the core concepts of Dojo has always been the <code>Deferred</code> class, and while the change to the "promise" architecture occurred in Dojo 1.5, it is worth discussing here, since its concepts are core to "modern" Dojo.  In "legacy" Dojo you would find a <code>Deferred</code> worked like this:</p>

<pre class="brush:js;">
  function createMyDeferred(){
    var myDeferred = new dojo.Deferred();
    setTimeout(function(){
      myDeferred.callback({ success: true });
    }, 1000);
    return myDeferred;
  }
  
  var deferred = createMyDeferred();
  deferred.addCallback(function(data){
    console.log("Success: " + data);
  });
  deferred.addErrback(function(err){
    console.log("Error: " + err);
  });
</pre>

<p>Now "modern" Dojo would work like this:</p>

<pre class="brush:js;">
  require(["dojo/_base/Deferred"], function(Deferred){
    function createMyDeferred(){
      var myDeferred = new Deferred();
      setTimeout(function(){
        myDeferred.resolve({ success: true });
      }, 1000);
      return myDeferred;
    }
    
    var deferred = createMyDeferred();
    deferred.then(function(data){
      console.log("Success: " + data);
    }, function(err){
      console.log("Error: " + err);
    });
  });
</pre>

<div class="proTip">There is quite a bit more to <code>Deferred</code>s, so check out the <a href="../deferreds/">Getting Started with Deferreds</a> tutorial.</div>

<h3>DOM Manipulation</h3>

<p>You might be seeing a trend here if you have gotten this far in the tutorial, in that not only has Dojo abandoned its dependency on the global namespace and adopted the some new patterns, it has also broken out some of "core" functionality into modules and what is more core to a JavaScript framework than DOM manipulation.</p>

<p>Well, that too has been broken up into much smaller chunks and modularized.  Here is summary of the modules and what they contain:</p>

<table class="info">
  <thead>
    <tr><th>Module</th><th>Description</th><th>Contains</th></tr>
  </thead>
  <tbody>
    <tr><td>dojo/dom</td><td>Core DOM functions</td><td>byId()<br/>isDescendant()<br/>setSelectable()</td></tr>
    <tr><td>dojo/dom-attr</td><td>DOM attribute functions</td><td>has()<br/>get()<br/>set()<br/>remove()<br/>getNodeProp()</td></tr>
    <tr><td>dojo/dom-class</td><td>DOM class functions</td><td>contains()<br/>add()<br/>remove()<br/>replace()<br/>toggle()</td></tr>
    <tr><td>dojo/dom-construct</td><td>DOM construction functions</td><td>toDom()<br/>place()<br/>create()<br/>empty()<br/>destroy()</td></tr>
    <tr><td>dojo/dom-form</td><td>Form handling functions</td><td>fieldToObject()<br/>toObject()<br/>toQuery()<br/>toJson()<br/></td></tr>
    <tr><td>dojo/io-query</td><td>String processing functions</td><td>objectToQuery()<br/>queryToObject()</td></tr>
    <tr><td>dojo/dom-geometry</td><td>DOM geometry related functions</td><td>position()<br/>getMarginBox()<br/>setMarginBox()<br/>getContentBox()<br/>setContentSize()<br/>getPadExtents()<br/>getBorderExtents()<br/>getPadBorderExtents()<br/>getMarginExtents()<br/>isBodyLtr()<br/>docScroll()<br/>fixIeBiDiScrollLeft()</td></tr>
    <tr><td>dojo/dom-prop</td><td>DOM property functions</td><td>get()<br/>set()</td></tr>
    <tr><td>dojo/dom-style</td><td>DOM style functions</td><td>getComputedStyle()<br/>get()<br/>set()</td></tr>
  </tbody>
</table>

<p>One of the things that is a consistent pattern across the "modern" Dojo toolkit is the separation of logic around accessors, in that instead of something like:</p>
<pre class="brush:js;">
  var node = dojo.byId("someNode");
  
  // Retrieves the value of the "value" DOM attribute
  var value = dojo.attr(node, "value");
  
  // Sets the value of the "value" DOM attribute
  dojo.attr(node, "value", "something");
</pre>

<p>Where the same function does two wholly different things depending on the arguments, versus something like:</p>
<pre class="brush:js;">
  require(["dojo/dom", "dojo/dom-attr"], function(dom, domAttr){
    var node = dom.byId("someNode");
    
    // Retrieves the value of the "value" DOM attribute
    var value = domAttr.get(node, "value");
    
    // Sets the value of the "value" DOM attribute
    domAttr.set(node, "value", "something");
  });
</pre>

<p>In the "modern" example, it is very clear what you are doing in the code and it become more difficult for your code to do something you didn't intend, because of an extra or missing argument.  This separation of accessors is consistent throughout "modern" Dojo.</p>

<h3>DataStores versus Stores</h3>

<p>In Dojo 1.6, the new <code>dojo/store</code> API was introduced and the <code>dojo/data</code> API was deprecated.  While the <code>dojo/data</code> datastores and <code>dojox/data</code> datastores are being maintained at least until Dojo 2.0, it is best to migrate to the new API when possible.  This tutorial cannot be exhaustive on the subject, but there is the <a href="../intro_dojo_store/">Dojo Object Store</a> tutorial available for further information.</p>

<div class="proTip">There is also the <a href="/reference-guide/dojo/store.html"><code>dojo/store</code></a> reference guide as well for detailed information on the API.</div>

<h3>Dijit and Widgets</h3>

<p>Dijit has also transformed itself in the "modern" world, but a lot of the changes have been in the underpinnings of the toolkit, with functionality being broken out into discreet building blocks and being combined together to make more complex functionality.  If you are creating a custom widget, you should read the <a href="../custom_widget">Creating a custom widget</a> tutorial.</p>
<p>If you are just developing with dijits or other widgets, then there were a few core concepts that were introduced with the <code>dojo/Stateful</code> and <code>dojo/Evented</code> classes.</p>

<p><code>dojo/Stateful</code> provides discreet accessors for widget attributes as well as the ability to "watch" changes to these attributes.  For example, you can do the following:</p>

<pre class="brush:js;">
  require(["dijit/form/Button", "dojo/domReady!"], function(Button){
    var button = new Button({
      label: "A label"
    }, "someNode");
    
    // Sets up a watch on button.label
    var handle = button.watch("label", function(attr, oldValue, newValue){
      console.log("button." + attr + " changed from '" + oldValue + "' to '" + newValue + "'");
    });
    
    // Gets the current label
    var label = button.get("label");
    console.log("button's current label: " + label);
    
    // This changes the value and should call the watch
    button.set("label", "A different label");
    
    // This will stop watching button.label
    handle.unwatch();
    
    button.set("label", "Even more different");
  });
</pre>
<a class="demoBtn demo" href="demo/watch.html">View Demo</a>

<p><code>dojo/Evented</code> provides <code>emit()</code> and <code>on()</code> functionality for classes and this is incorporated into Dijits and widgets.  In particular, it is "modern" to use <code>widget.on()</code> to set your event handling.  For example, you can do the following:</p>

<pre class="brush:js;">
  require(["dijit/form/Button", "dojo/domReady!"], function(Button){
    var button = new Button({
      label: "Click Me!"
    }, "someNode");
    
    // Sets the event handling for the button
    button.on("click", function(e){
      console.log("I was clicked!", e);
    });
  });
</pre>
<a class="demoBtn demo" href="demo/on.html">View Demo</a>

<h3>Parser</h3>

<p>Finally, there is the <code>dojo/parser</code>.  Dojo has had strength in both a programmatic and declarative markup way, with the <code>dojo/parser</code> handling the interpretation of the declarative markup and converting that into instantiated objects and widgets.  All of the "modern" thinking mentioned above has had an impact on the <code>dojo/parser</code> as well as there has been some "modern" changes of its own.</p>

<p>While the <code>parseOnLoad: true</code> Dojo configuration is still supported, it usually makes more sense to invoke parser specifically.  For example:</p>
<pre class="brush:js;">
  require(["dojo/parser", "dojo/domReady!"], function(parser){
    parser.parse();
  });
</pre>

<p>One of the other "big" changes with the parser is that it supports HTML5 compliant attributes to markup the nodes.  This allows your marked-up HTML to be valid in HTML5.  In particular <code>dojoType</code> changes to <code>data-dojo-type</code> and instead of specify object parameters as non-valid attributes, all parameters to be passed to the object constructor are specified in the <code>data-dojo-props</code> attribute.  For example:</p>
<pre class="brush:js; html-script:true;">
  &lt;button data-dojo-type="dijit.form.Button" tabIndex=2 
      data-dojo-props="iconClass: 'checkmark'"&gt;OK&lt;/button&gt;
</pre>

<div class="proTip">In Dojo 1.8 <code>data-dojo-type</code> will be able to accept the MID instead of the class name for objects.  For example <code>data-dojo-type="dijit.form.Button"</code> becomes <code>data-dojo-type="dijit/form/Button"</code>.  There are some other enhancements to the parser in 1.8 as well.</div>
<br />
<p>With the changes mentioned above in regards to the concepts introduced with <code>dojo/Evented</code> and <code>dojo/Stateful</code> the parser has kept pace with the declarative scripting and added appropriate script types to replicate the "watch" and "on" functionality.  For example, you can now do:</p>
<pre class="brush:js; html-script:true;">
  &lt;button data-dojo-type="dijit.form.Button" type="button"&gt;
    &lt;span&gt;Click&lt;/span&gt;
    &lt;script type="dojo/on" data-dojo-event="click" data-dojo-args="e"&gt;
      console.log("I was clicked!", e);
      this.set("label", "Clicked!");
    &lt;/script&gt;
    &lt;script type="dojo/watch" data-dojo-prop="label" data-dojo-args="prop, oldValue, newValue"&gt;
      console.log("button: " + prop + " changed from '" + oldValue + "' to '" + newValue + "'");
    &lt;/script&gt;
  &lt;/button&gt;
</pre>
<a class="demoBtn demo" href="demo/parser.html">View Demo</a>

<h3>Builder</h3>

<p>The final area to briefly touch on in this tutorial is the Dojo builder.  In Dojo 1.7 it was completely rewritten.  Partly it was to handle the significant changes with AMD, but it was also designed to modernize it and make it very feature rich.  It is a topic to vast for this tutorial.  You should read the <a href="../build/">Creating Builds</a> tutorial for information, but be prepared to forget everything you knew about the old builder in order to embrace the "modern" builder.</p>

<h3>Conclusion</h3>
<p>Hopefully your journey into the "modern" world of Dojo hasn't been too traumatic.  While it takes a while for anyone familiar with the "legacy" world to start thinking the "Dojo way" in the new world, once you have made the move, it will be hard to go back and you will find you have more structured approach to your applications.</p>
<p>When all else fails, remember the "modern" Dojo way is:</p>
<ul>
  <li><strong>Granular Dependencies and Modular</strong> &mdash; only require what you need when you need it.  Say goodbye to the "kitchen sink".  It makes for faster/smarter/safer apps.</li>
  <li><strong>Asynchronous</strong> &mdash; things do not necessarily happen in order, think of things in being asynchronous and less bad things will happen.</li>
  <li><strong>Global Scope is Bad</strong> &mdash; one more time, repeat after me, "I will not use the global scope."</li>
  <li><strong>Discreet Accessors</strong> &mdash; a function only does one thing, especially when it comes to accessors.  There is a <code>get()</code> and a <code>set()</code> for what you want to do.</li>
  <li><strong>Dojo compliments ES5</strong> &mdash; if EcmaScript 5 does something (and it is "shimmable") then Dojo doesn't want to do it.</li>
  <li><strong>Events and Aspects, not Connections</strong> &mdash; Dojo is migrating away from "generic" connections to focus on events and aspect oriented programming.</li>
  <li><strong>The Builder is a Different Beast</strong> &mdash; it is much stronger, more powerful and feature rich, but it will only go to highlight bad design assumptions in "legacy" applications, not fix them.</li>
</ul>
<p>Good luck!</p>

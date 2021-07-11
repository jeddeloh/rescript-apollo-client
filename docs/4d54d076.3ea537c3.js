(window.webpackJsonp = window.webpackJsonp || []).push([
  [8],
  {
    64: function (e, t, n) {
      "use strict";
      n.r(t),
        n.d(t, "frontMatter", function () {
          return r;
        }),
        n.d(t, "metadata", function () {
          return s;
        }),
        n.d(t, "rightToc", function () {
          return l;
        }),
        n.d(t, "default", function () {
          return c;
        });
      var a = n(2),
        i = n(6),
        o = (n(0), n(74)),
        r = { id: "contributing", title: "Contributing" },
        s = {
          unversionedId: "contributing",
          id: "contributing",
          isDocsHomePage: !1,
          title: "Contributing",
          description:
            "Lets work to make the Apollo experience in ReScript the best experience out there!",
          source: "@site/docs/contributing.md",
          slug: "/contributing",
          permalink: "/rescript-apollo-client/docs/contributing",
          editUrl:
            "https://github.com/reasonml-community/rescript-apollo-client/edit/master/documentation/docs/contributing.md",
          version: "current",
        },
        l = [
          {
            value: "Core Philosopies",
            id: "core-philosopies",
            children: [
              {
                value: "Following a Consistent Pattern",
                id: "following-a-consistent-pattern",
                children: [],
              },
              {
                value: "Avoiding Partial Types",
                id: "avoiding-partial-types",
                children: [],
              },
            ],
          },
          {
            value: "Style Guidelines",
            id: "style-guidelines",
            children: [
              {
                value: "Directory Structure and Module Naming",
                id: "directory-structure-and-module-naming",
                children: [],
              },
              { value: "Types", id: "types", children: [] },
              {
                value: "Binding to Js Module Exports",
                id: "binding-to-js-module-exports",
                children: [],
              },
              {
                value: "Binding to Methods",
                id: "binding-to-methods",
                children: [],
              },
              {
                value: "Binding to Objects",
                id: "binding-to-objects",
                children: [],
              },
              {
                value: "Binding to Enums",
                id: "binding-to-enums",
                children: [],
              },
              { value: "General", id: "general", children: [] },
              {
                value: "Reasoning behind <code>Js_</code> modules",
                id: "reasoning-behind-js_-modules",
                children: [],
              },
            ],
          },
        ],
        p = { rightToc: l };
      function c(e) {
        var t = e.components,
          n = Object(i.a)(e, ["components"]);
        return Object(o.b)(
          "wrapper",
          Object(a.a)({}, p, n, { components: t, mdxType: "MDXLayout" }),
          Object(o.b)(
            "p",
            null,
            "Lets work to make the Apollo experience in ReScript the best experience out there!"
          ),
          Object(o.b)("h2", { id: "core-philosopies" }, "Core Philosopies"),
          Object(o.b)(
            "ul",
            null,
            Object(o.b)(
              "li",
              { parentName: "ul" },
              "Provide 1:1 mapping to Javascript ",
              Object(o.b)("em", { parentName: "li" }, "then"),
              ' use those as building blocks for more "reasonable" ergonomics'
            ),
            Object(o.b)(
              "li",
              { parentName: "ul" },
              "Follow a consistent pattern for bindings"
            ),
            Object(o.b)(
              "li",
              { parentName: "ul" },
              "Avoid partial types or bindings if possible"
            ),
            Object(o.b)(
              "li",
              { parentName: "ul" },
              "Encourage incremental contribution from the community rather than biting off more than one person can chew"
            )
          ),
          Object(o.b)(
            "p",
            null,
            "There's nothing fancy about this library. It tends to view the problem of bindings as a people problem rather than a programming problem (all the hard work has already been done for us by Graphql-ppx) As such, a lot of detail is paid to consistency and clarity with the hope of maximizing human ability to both add and verify that bindings are correct. The long-term success or failure of this library is will likely be dependent on active community contribution rather than the efforts of a few individuals."
          ),
          Object(o.b)(
            "h3",
            { id: "following-a-consistent-pattern" },
            "Following a Consistent Pattern"
          ),
          Object(o.b)(
            "p",
            null,
            "At the file level, bindings to Javascript packages should mirror the directory structure in the JS package. This is critically important! It should be easy for anyone else to see exactly what is being bound and if anything is missing or incorrect. This has the side benefit of being able to navigate to any import you see in the javascript docs via filepath pattern, but it's primary purpose is consistency."
          ),
          Object(o.b)(
            "p",
            null,
            "At the code level, all JS bindings should go in a ",
            Object(o.b)("inlineCode", { parentName: "p" }, "Js_"),
            " module of some sort. At first it seems ridiculous, but it pays off at scale. (See ",
            Object(o.b)(
              "strong",
              { parentName: "p" },
              "Reasoning Behind ",
              Object(o.b)("inlineCode", { parentName: "strong" }, "Js_"),
              " modules"
            ),
            ")"
          ),
          Object(o.b)(
            "h3",
            { id: "avoiding-partial-types" },
            "Avoiding Partial Types"
          ),
          Object(o.b)(
            "p",
            null,
            "Please type something as completely as possible when you come across it or leave it for someone else (if nothing else, you can use an abstract type so things will still flow through everywhere and people can cast it when in a hurry). This way no one has to go back and duplicate that work of tracing through the same code you were just in ",
            Object(o.b)("em", { parentName: "p" }, "and"),
            " we can trust that if a binding exists, it's probably complete and we can just reuse."
          ),
          Object(o.b)("h2", { id: "style-guidelines" }, "Style Guidelines"),
          Object(o.b)(
            "h3",
            { id: "directory-structure-and-module-naming" },
            "Directory Structure and Module Naming"
          ),
          Object(o.b)(
            "p",
            null,
            "Each directory should have a corresponding Reason module."
          ),
          Object(o.b)(
            "pre",
            null,
            Object(o.b)(
              "code",
              Object(a.a)({ parentName: "pre" }, {}),
              "@apollo/client/react/hooks/useQuery.js\n"
            )
          ),
          Object(o.b)("p", null, "should become"),
          Object(o.b)(
            "pre",
            null,
            Object(o.b)(
              "code",
              Object(a.a)({ parentName: "pre" }, {}),
              "src/react/hooks/ApolloClient__React_Hooks_UseQuery.res\n"
            )
          ),
          Object(o.b)(
            "h4",
            { id: "breaking-it-down-12__3_4" },
            "Breaking it down: ",
            Object(o.b)("inlineCode", { parentName: "h4" }, "/[1]/[2]__[3]_[4]")
          ),
          Object(o.b)(
            "ol",
            null,
            Object(o.b)(
              "li",
              { parentName: "ol" },
              "ReScript files should be located in the same directory structure as the js counterpart (usually there is a ",
              Object(o.b)("inlineCode", { parentName: "li" }, ".d.ts"),
              " for every ",
              Object(o.b)("inlineCode", { parentName: "li" }, ".js"),
              " file so we can think of them interchangeably)"
            ),
            Object(o.b)(
              "li",
              { parentName: "ol" },
              "All module names should be prefixed with ",
              Object(o.b)("inlineCode", { parentName: "li" }, "ApolloClient__"),
              ' "namespace"'
            ),
            Object(o.b)(
              "li",
              { parentName: "ol" },
              "File names reflect the directory structure"
            ),
            Object(o.b)(
              "li",
              { parentName: "ol" },
              "Files should be named the same as the js counterpart"
            )
          ),
          Object(o.b)("h3", { id: "types" }, "Types"),
          Object(o.b)(
            "ul",
            null,
            Object(o.b)(
              "li",
              { parentName: "ul" },
              "Please use the same naming as typescript where possible"
            ),
            Object(o.b)(
              "li",
              { parentName: "ul" },
              "Every type goes in its own module with a ",
              Object(o.b)("inlineCode", { parentName: "li" }, "type t"),
              " (exception: see SubStypes)"
            ),
            Object(o.b)(
              "li",
              { parentName: "ul" },
              "Every type module should contain a ",
              Object(o.b)("inlineCode", { parentName: "li" }, "type t"),
              ", a ",
              Object(o.b)("inlineCode", { parentName: "li" }, "Js_"),
              " module with a ",
              Object(o.b)("inlineCode", { parentName: "li" }, "type t"),
              ", and a ",
              Object(o.b)("inlineCode", { parentName: "li" }, "toJs"),
              " or ",
              Object(o.b)("inlineCode", { parentName: "li" }, "fromJs"),
              " conversion function. ",
              Object(o.b)("inlineCode", { parentName: "li" }, "t => Js_.t"),
              " or ",
              Object(o.b)("inlineCode", { parentName: "li" }, "Js_.t => t")
            ),
            Object(o.b)(
              "li",
              { parentName: "ul" },
              "Paste the type definition from the ",
              Object(o.b)("inlineCode", { parentName: "li" }, ".d.ts"),
              " file above the ",
              Object(o.b)("inlineCode", { parentName: "li" }, "type t"),
              " in the ",
              Object(o.b)("inlineCode", { parentName: "li" }, "Js_"),
              " module"
            ),
            Object(o.b)(
              "li",
              { parentName: "ul" },
              "If data requires parsing/serializing create a new record even if the shape is the same. This ensures you don't forget to parse somewhere."
            ),
            Object(o.b)(
              "li",
              { parentName: "ul" },
              "Prefer single types when the more complicated type in a union can express both ",
              Object(o.b)(
                "inlineCode",
                { parentName: "li" },
                "shouldResubscribe?: boolean | ((options: BaseSubscriptionOptions<TData, TVariables>) => boolean);"
              )
            ),
            Object(o.b)(
              "li",
              { parentName: "ul" },
              "Do all of this even if it doesn't need it (See Reasoning Behind ",
              Object(o.b)("inlineCode", { parentName: "li" }, "Js_"),
              " modules)"
            )
          ),
          Object(o.b)("p", null, "Example:"),
          Object(o.b)(
            "pre",
            null,
            Object(o.b)(
              "code",
              Object(a.a)({ parentName: "pre" }, {}),
              "// #1 - create a Js_ module for your type\nmodule Js_ = {\n  // #2 - paste the definition from the .js file here\n  // #3 - add the `.js` representation of type t = ...\n}\n\n// #4  - add the ReScript representation of type t\n// #4a - you can use `type t = Js_.t` if they are _exactly_ the same\n// #4b - if they are the exact same _shape_ but requires parsing or serializing, *define a new record of the same shape* so we can leverage the fact that records are nominally typed to prevent someone forgetting to convert somewhere\n\n// #5 - add `toJs` or `fromJs`. They often require parsing: `let fromJs: Js_.t('jsData, ~parse: 'jsData => 'data) => t('data)`\n"
            )
          ),
          Object(o.b)("h4", { id: "subtypes" }, "SubTypes"),
          Object(o.b)(
            "p",
            null,
            "Sometimes multiple types were required to represent a single type in TypeScript. In order to help make it clear what is a binding to an actual type and what is just needed by ReScript, we take a similar naming approach to the modules (prefixing with the parent). For instance, ",
            Object(o.b)(
              "inlineCode",
              { parentName: "p" },
              "Apollo_Client__React_Types.QueryResult.Raw"
            ),
            " has a ",
            Object(o.b)("inlineCode", { parentName: "p" }, "type t"),
            " that uses ",
            Object(o.b)(
              "inlineCode",
              { parentName: "p" },
              "t_fetchMoreOptions"
            ),
            " which in turn uses ",
            Object(o.b)(
              "inlineCode",
              { parentName: "p" },
              "t_fetchMoreOptions_updateQueryOptions"
            ),
            "."
          ),
          Object(o.b)(
            "h3",
            { id: "binding-to-js-module-exports" },
            "Binding to Js Module Exports"
          ),
          Object(o.b)(
            "p",
            null,
            Object(o.b)("inlineCode", { parentName: "p" }, "externals"),
            " go under a ",
            Object(o.b)("inlineCode", { parentName: "p" }, "Js_"),
            " module and any types they reference should be ",
            Object(o.b)("inlineCode", { parentName: "p" }, "Js_.t"),
            " versions."
          ),
          Object(o.b)("h3", { id: "binding-to-methods" }, "Binding to Methods"),
          Object(o.b)(
            "p",
            null,
            "Prefer T-first with ",
            Object(o.b)("inlineCode", { parentName: "p" }, "[@send]"),
            ". Again, ",
            Object(o.b)("inlineCode", { parentName: "p" }, "externals"),
            " go under a ",
            Object(o.b)("inlineCode", { parentName: "p" }, "Js_"),
            " module with a ",
            Object(o.b)("inlineCode", { parentName: "p" }, "type t"),
            " and any types they reference should be ",
            Object(o.b)("inlineCode", { parentName: "p" }, "Js_.t"),
            " versions."
          ),
          Object(o.b)("h3", { id: "binding-to-objects" }, "Binding to Objects"),
          Object(o.b)("p", null, "Use records"),
          Object(o.b)("h3", { id: "binding-to-enums" }, "Binding to Enums"),
          Object(o.b)(
            "p",
            null,
            "Prefer standard variants. ",
            Object(o.b)("inlineCode", { parentName: "p" }, "jsConverter"),
            " works great for ints, but otherwise use manual ",
            Object(o.b)("inlineCode", { parentName: "p" }, "toJs"),
            " and ",
            Object(o.b)("inlineCode", { parentName: "p" }, "fromJs"),
            " functions. Standard variants are just nicer to consume in other places and this keeps consistency"
          ),
          Object(o.b)("h3", { id: "general" }, "General"),
          Object(o.b)(
            "ul",
            null,
            Object(o.b)(
              "li",
              { parentName: "ul" },
              "Prefer T-first because that's the Reason community default"
            ),
            Object(o.b)(
              "li",
              { parentName: "ul" },
              "Hooks are T-last because that makes sense given their usage"
            ),
            Object(o.b)(
              "li",
              { parentName: "ul" },
              "ApolloClient methods are a Frankenstein T-first ",
              Object(o.b)("em", { parentName: "li" }, "and"),
              " T-last because they want to maintain similarity with hooks api, but are also T-first due to ",
              "[@send]",
              " and T-first preference"
            )
          ),
          Object(o.b)(
            "h3",
            { id: "reasoning-behind-js_-modules" },
            "Reasoning behind ",
            Object(o.b)("inlineCode", { parentName: "h3" }, "Js_"),
            " modules"
          ),
          Object(o.b)("p", null, "Here's a typical example:"),
          Object(o.b)(
            "pre",
            null,
            Object(o.b)(
              "code",
              Object(a.a)({ parentName: "pre" }, {}),
              "module TypeName = {\n  module Js_ = {\n    type t;\n  }\n\n  type t = Js_.t;\n};\n"
            )
          ),
          Object(o.b)(
            "p",
            null,
            "Not much point yet, but bear with me, it pays off in the big picture. What if we need to parse/serialize some data which happens a lot in this library?"
          ),
          Object(o.b)(
            "pre",
            null,
            Object(o.b)(
              "code",
              Object(a.a)(
                { parentName: "pre" },
                { className: "language-diff" }
              ),
              "module TypeName = {\n  module Js_ = {\n-   type t;\n+   type t('jsData) = {\n+     data: 'jsData,\n+   };\n  }\n\n- type t = Js_.t;\n+ type t('data) = {\n+   data: 'data\n+ };\n\n+ let toJs: t => Js_.t = (t, ~serialize) => {\n+   data: serialize(t.data)\n+ };\n};\n"
            )
          ),
          Object(o.b)(
            "p",
            null,
            "Nice, now when wherever we say we want a ",
            Object(o.b)("inlineCode", { parentName: "p" }, "Typename.t"),
            ", we can never forget to parse because records are nominally typed."
          ),
          Object(o.b)(
            "p",
            null,
            "What if you need to construct a class or object with a bunch of optional properties?"
          ),
          Object(o.b)(
            "pre",
            null,
            Object(o.b)(
              "code",
              Object(a.a)(
                { parentName: "pre" },
                { className: "language-diff" }
              ),
              "module TypeName = {\n  module Js_ = {\n    type t('jsData) = {\n      data: 'jsData,\n+     optionalProp: option(bool),\n    };\n\n+   type make_options('jsData) = {\n+     data: 'jsData,\n+     optionalProp: option(bool),\n+   }\n\n+   [@new] [@module \"someModule\"]\n+   external make = (make_options('jsData)) => t = \"someClass\";\n  }\n\n  type t('data) = {\n    data: 'data,\n+   optionalProp: option(bool),\n  };\n\n  let toJs: t => Js_.t = (t) => {\n    data: serialize(t.data)\n+   optionalProp: t.optionalProp\n  };\n\n+ let make: (~data, ~optionalProp=?, ()) =>\n+   Js_.make(\n+     toJs({\n+         data,\n+         optionalProp\n+       },\n+       ~serialize,\n+     )\n+   );\n};\n"
            )
          ),
          Object(o.b)(
            "p",
            null,
            "It's nice to have all this conversion stuff wrapped in one module and have consistent naming. All of it together really begins to pay off when we have types that reference many other types."
          ),
          Object(o.b)(
            "pre",
            null,
            Object(o.b)(
              "code",
              Object(a.a)(
                { parentName: "pre" },
                { className: "language-diff" }
              ),
              "module TypeName = {\n  module Js_ = {\n    type t('jsData) = {\n      data: 'jsData,\n+     reusedType: ReusedType.Js_.t\n    };\n\n    type make_options('jsData) = {\n      data: 'jsData,\n      optionalProp: option(bool),\n+     reusedType: ReusedType.Js_.t\n    }\n    [@new] [@module \"someModule\"]\n    external make = (make_options('jsData)) => t = \"someClass\";\n  }\n\n  type t('data) = {\n    data: 'data,\n    optionalProp: option(bool),\n+   reusedType: ReusedType.t\n  };\n\n- let toJs: t => Js_.t = (t) => {\n+ let toJs: t => Js_.t = (t, ~serialize) => {\n    data: serialize(t.data)\n    optionalProp: t.optionalProp\n+   reusedType: t.reusedType->ReusedType.toJs(~serialize)\n  };\n\n- let make: (~data, ~optionalProp=?, ()) =>\n+ let make: (~data, ~optionalProp=?, ~reusedType, ~serialize, ()) =>\n    Js_.make(\n      toJs({\n          data,\n          optionalProp\n+         reusedType\n        },\n        ~serialize,\n      )\n    );\n};\n"
            )
          ),
          Object(o.b)(
            "p",
            null,
            "Does ",
            Object(o.b)("inlineCode", { parentName: "p" }, "reusedType"),
            " need some conversion or parsing or serializing? If we've done things right, all we need to confirm is that any ",
            Object(o.b)("inlineCode", { parentName: "p" }, "Js_"),
            " modules reference the ",
            Object(o.b)("inlineCode", { parentName: "p" }, "Js_.t"),
            " versions of types, the compiler will do the rest! In this case, it turns out it needs also needs parse!"
          ),
          Object(o.b)(
            "pre",
            null,
            Object(o.b)(
              "code",
              Object(a.a)(
                { parentName: "pre" },
                { className: "language-diff" }
              ),
              "module TypeName = {\n  module Js_ = {\n    type t('jsData) = {\n      data: 'jsData,\n      reusedType: ReusedType.Js_.t\n    };\n\n    type make_options('jsData) = {\n      data: 'jsData,\n      optionalProp: option(bool),\n      reusedType: ReusedType.Js_.t\n    }\n    [@new] [@module \"someModule\"]\n    external make = (make_options('jsData)) => t = \"someClass\";\n  }\n\n  type t('data) = {\n    data: 'data,\n    optionalProp: option(bool),\n    reusedType: ReusedType.t\n  };\n\n- let toJs: t => Js_.t = (t, ~serialize) => {\n+ let toJs: t => Js_.t = (t, ~parse, ~serialize) => {\n    data: serialize(t.data)\n    optionalProp: t.optionalProp\n-   reusedType: t.reusedType->ReusedType.toJs(~serialize)\n+   reusedType: t.reusedType->ReusedType.toJs(~parse, ~serialize)\n  };\n\n- let make: (~data, ~optionalProp=?, ~reusedType, ~serialize, ()) =>\n+ let make: (~data, ~optionalProp=?, ~parse, ~reusedType, ~serialize, ()) =>\n    Js_.make(\n      toJs({\n          data,\n          optionalProp\n          reusedType\n        },\n        ~serialize,\n      )\n    );\n};\n"
            )
          )
        );
      }
      c.isMDXComponent = !0;
    },
    74: function (e, t, n) {
      "use strict";
      n.d(t, "a", function () {
        return d;
      }),
        n.d(t, "b", function () {
          return m;
        });
      var a = n(0),
        i = n.n(a);
      function o(e, t, n) {
        return (
          t in e
            ? Object.defineProperty(e, t, {
                value: n,
                enumerable: !0,
                configurable: !0,
                writable: !0,
              })
            : (e[t] = n),
          e
        );
      }
      function r(e, t) {
        var n = Object.keys(e);
        if (Object.getOwnPropertySymbols) {
          var a = Object.getOwnPropertySymbols(e);
          t &&
            (a = a.filter(function (t) {
              return Object.getOwnPropertyDescriptor(e, t).enumerable;
            })),
            n.push.apply(n, a);
        }
        return n;
      }
      function s(e) {
        for (var t = 1; t < arguments.length; t++) {
          var n = null != arguments[t] ? arguments[t] : {};
          t % 2
            ? r(Object(n), !0).forEach(function (t) {
                o(e, t, n[t]);
              })
            : Object.getOwnPropertyDescriptors
            ? Object.defineProperties(e, Object.getOwnPropertyDescriptors(n))
            : r(Object(n)).forEach(function (t) {
                Object.defineProperty(
                  e,
                  t,
                  Object.getOwnPropertyDescriptor(n, t)
                );
              });
        }
        return e;
      }
      function l(e, t) {
        if (null == e) return {};
        var n,
          a,
          i = (function (e, t) {
            if (null == e) return {};
            var n,
              a,
              i = {},
              o = Object.keys(e);
            for (a = 0; a < o.length; a++)
              (n = o[a]), t.indexOf(n) >= 0 || (i[n] = e[n]);
            return i;
          })(e, t);
        if (Object.getOwnPropertySymbols) {
          var o = Object.getOwnPropertySymbols(e);
          for (a = 0; a < o.length; a++)
            (n = o[a]),
              t.indexOf(n) >= 0 ||
                (Object.prototype.propertyIsEnumerable.call(e, n) &&
                  (i[n] = e[n]));
        }
        return i;
      }
      var p = i.a.createContext({}),
        c = function (e) {
          var t = i.a.useContext(p),
            n = t;
          return e && (n = "function" == typeof e ? e(t) : s(s({}, t), e)), n;
        },
        d = function (e) {
          var t = c(e.components);
          return i.a.createElement(p.Provider, { value: t }, e.children);
        },
        b = {
          inlineCode: "code",
          wrapper: function (e) {
            var t = e.children;
            return i.a.createElement(i.a.Fragment, {}, t);
          },
        },
        u = i.a.forwardRef(function (e, t) {
          var n = e.components,
            a = e.mdxType,
            o = e.originalType,
            r = e.parentName,
            p = l(e, ["components", "mdxType", "originalType", "parentName"]),
            d = c(n),
            u = a,
            m = d["".concat(r, ".").concat(u)] || d[u] || b[u] || o;
          return n
            ? i.a.createElement(m, s(s({ ref: t }, p), {}, { components: n }))
            : i.a.createElement(m, s({ ref: t }, p));
        });
      function m(e, t) {
        var n = arguments,
          a = t && t.mdxType;
        if ("string" == typeof e || a) {
          var o = n.length,
            r = new Array(o);
          r[0] = u;
          var s = {};
          for (var l in t) hasOwnProperty.call(t, l) && (s[l] = t[l]);
          (s.originalType = e),
            (s.mdxType = "string" == typeof e ? e : a),
            (r[1] = s);
          for (var p = 2; p < o; p++) r[p] = n[p];
          return i.a.createElement.apply(null, r);
        }
        return i.a.createElement.apply(null, n);
      }
      u.displayName = "MDXCreateElement";
    },
  },
]);

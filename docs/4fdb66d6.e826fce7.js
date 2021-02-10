(window.webpackJsonp=window.webpackJsonp||[]).push([[9],{65:function(e,t,n){"use strict";n.r(t),n.d(t,"frontMatter",(function(){return i})),n.d(t,"metadata",(function(){return s})),n.d(t,"rightToc",(function(){return c})),n.d(t,"default",(function(){return u}));var o=n(2),r=n(6),a=(n(0),n(74)),i={id:"mutations",title:"Mutations",sidebar_label:"Mutations"},s={unversionedId:"mutations",id:"mutations",isDocsHomePage:!1,title:"Mutations",description:"Using React Hooks",source:"@site/docs/mutations.md",slug:"/mutations",permalink:"/rescript-apollo-client/docs/mutations",editUrl:"https://github.com/reasonml-community/rescript-apollo-client/blob/github-pages/documentationWebsite/docs/mutations.md",version:"current",sidebar_label:"Mutations",sidebar:"docs",previous:{title:"Queries",permalink:"/rescript-apollo-client/docs/queries"},next:{title:"Subscriptions",permalink:"/rescript-apollo-client/docs/subscriptions"}},c=[{value:"Using React Hooks",id:"using-react-hooks",children:[{value:"Basic usage",id:"basic-usage",children:[]},{value:"Post-Mutation Updates",id:"post-mutation-updates",children:[]}]},{value:"Directly Via the Apollo Client",id:"directly-via-the-apollo-client",children:[]}],l={rightToc:c};function u(e){var t=e.components,n=Object(r.a)(e,["components"]);return Object(a.b)("wrapper",Object(o.a)({},l,n,{components:t,mdxType:"MDXLayout"}),Object(a.b)("h2",{id:"using-react-hooks"},"Using React Hooks"),Object(a.b)("h3",{id:"basic-usage"},"Basic usage"),Object(a.b)("p",null,"Create a mutation module using ",Object(a.b)("inlineCode",{parentName:"p"},"graphql-ppx"),". We'll use this throughout the examples on this page."),Object(a.b)("pre",null,Object(a.b)("code",{parentName:"pre"},"module AddTodoMutation = %graphql(\n  `\n    mutation AddTodo($text: String!) {\n      todo: addTodoSimple(text: $text) {\n        id\n        completed\n        text\n      }\n    }\n  `\n)\n")),Object(a.b)("p",null,"Call the ",Object(a.b)("inlineCode",{parentName:"p"},"use")," hook in a component"),Object(a.b)("pre",null,Object(a.b)("code",{parentName:"pre",className:"language-reason"},'@react.component\nlet make = () => {\n  let (mutate, _mutationResult) = AddTodoMutation.use()\n\n  <button onClick={_ => mutate({text: "Some text"})->ignore}>\n    {"Add To-Do"->React.string}\n  </button>\n}\n')),Object(a.b)("h3",{id:"post-mutation-updates"},"Post-Mutation Updates"),Object(a.b)("p",null,"This section needs improvements, but for now here's an examples of refetching data after a mutation, updating the cache, and optimistic updates."),Object(a.b)("pre",null,Object(a.b)("code",{parentName:"pre",className:"language-reason"},'@react.component\nlet make = () => {\n  let (mutate, result) = AddTodoMutation.use()\n\n  switch result {\n  | {called: false} => <>\n      {"Not called... "->React.string}\n      <button\n        onClick={_ =>\n          mutate(\n            ~optimisticResponse=_variables => {\n              todo: {\n                __typename: "TodoItem",\n                id: "optimisticResponseTodo",\n                completed: None,\n                text: "To-Do from optimisticRespomse",\n              },\n            },\n            ~update=({writeFragment, writeQuery}, {data}) =>\n              switch data {\n              | Some({todo}) =>\n                // Apollo docs use cache.modify, but it\'s not typesafe. I recommend some\n                // combination of readQuery / writeQuery / writeFragment\n                Js.log2("mutate.update To-Do: ", todo)\n                let _unusedRef = writeFragment(\n                  ~fragment=module(Fragments.TodoItem),\n                  ~data={\n                    __typename: todo.__typename,\n                    id: "fragmentToDo",\n                    completed: None,\n                    text: "To-Do from writeFragment",\n                  },\n                  (),\n                )\n                let _unusedRef = writeQuery(\n                  ~query=module(TodosQuery),\n                  ~data={\n                    todos: [\n                      {\n                        __typename: todo.__typename,\n                        id: "writeQueryToDo",\n                        completed: None,\n                        text: "To-Do from writeQuery",\n                      },\n                    ],\n                  },\n                  (),\n                )\n              | None => ()\n              },\n            ~refetchQueries=[\n              TodosQuery.refetchQueryDescription(),\n              // - OR -\n              String("TodosQuery"),\n            ],\n            {text: "Another To-Do"},\n          )->ignore}>\n        {"Add To-Do (all the bells and whistles)"->React.string}\n      </button>\n    </>\n  | {loading: true} => "Loading..."->React.string\n  | {data: Some({todo: {text}}), error: None} =>\n    <p> {React.string("To-Do added: \\"" ++ (text ++ "\\""))} </p>\n  | {error} => <>\n      {"Error loading data"->React.string}\n      {switch error {\n      | Some(error) => React.string(": " ++ error.message)\n      | None => React.null\n      }}\n    </>\n  }\n}\n')),Object(a.b)("h2",{id:"directly-via-the-apollo-client"},"Directly Via the Apollo Client"),Object(a.b)("pre",null,Object(a.b)("code",{parentName:"pre",className:"language-reason"},'let addTodo = _ =>\n  // This assumes you\'ve set up a Client module as in the Getting Started section\n  Apollo.client.mutate(~mutation=module(AddTodoMutation), {text: "Another To-Do"})\n  ->Promise.map(result =>\n    switch result {\n    | Ok({data}) => Js.log2("mutate result: ", data)\n    | Error(error) => Js.log2("Error: ", error)\n    }\n  )\n  ->ignore\n')))}u.isMDXComponent=!0},74:function(e,t,n){"use strict";n.d(t,"a",(function(){return d})),n.d(t,"b",(function(){return b}));var o=n(0),r=n.n(o);function a(e,t,n){return t in e?Object.defineProperty(e,t,{value:n,enumerable:!0,configurable:!0,writable:!0}):e[t]=n,e}function i(e,t){var n=Object.keys(e);if(Object.getOwnPropertySymbols){var o=Object.getOwnPropertySymbols(e);t&&(o=o.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),n.push.apply(n,o)}return n}function s(e){for(var t=1;t<arguments.length;t++){var n=null!=arguments[t]?arguments[t]:{};t%2?i(Object(n),!0).forEach((function(t){a(e,t,n[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(n)):i(Object(n)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(n,t))}))}return e}function c(e,t){if(null==e)return{};var n,o,r=function(e,t){if(null==e)return{};var n,o,r={},a=Object.keys(e);for(o=0;o<a.length;o++)n=a[o],t.indexOf(n)>=0||(r[n]=e[n]);return r}(e,t);if(Object.getOwnPropertySymbols){var a=Object.getOwnPropertySymbols(e);for(o=0;o<a.length;o++)n=a[o],t.indexOf(n)>=0||Object.prototype.propertyIsEnumerable.call(e,n)&&(r[n]=e[n])}return r}var l=r.a.createContext({}),u=function(e){var t=r.a.useContext(l),n=t;return e&&(n="function"==typeof e?e(t):s(s({},t),e)),n},d=function(e){var t=u(e.components);return r.a.createElement(l.Provider,{value:t},e.children)},p={inlineCode:"code",wrapper:function(e){var t=e.children;return r.a.createElement(r.a.Fragment,{},t)}},m=r.a.forwardRef((function(e,t){var n=e.components,o=e.mdxType,a=e.originalType,i=e.parentName,l=c(e,["components","mdxType","originalType","parentName"]),d=u(n),m=o,b=d["".concat(i,".").concat(m)]||d[m]||p[m]||a;return n?r.a.createElement(b,s(s({ref:t},l),{},{components:n})):r.a.createElement(b,s({ref:t},l))}));function b(e,t){var n=arguments,o=t&&t.mdxType;if("string"==typeof e||o){var a=n.length,i=new Array(a);i[0]=m;var s={};for(var c in t)hasOwnProperty.call(t,c)&&(s[c]=t[c]);s.originalType=e,s.mdxType="string"==typeof e?e:o,i[1]=s;for(var l=2;l<a;l++)i[l]=n[l];return r.a.createElement.apply(null,i)}return r.a.createElement.apply(null,n)}m.displayName="MDXCreateElement"}}]);
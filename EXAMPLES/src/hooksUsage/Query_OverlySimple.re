module TodosQuery = [%graphql
  {|
    query TodosQuery {
      todos: allTodos {
        id
        text
        completed
      }
    }
  |}
];

[@react.component]
let make = () => {
  switch (TodosQuery.use()) {
  | {loading: true} => "Loading..."->React.string
  | {error: Some(_error)} => "Error loading data"->React.string
  | {data: Some({todos})} =>
    <div>
      "There are "->React.string
      {todos->Belt.Array.length->React.int}
      " To-Dos"->React.string
    </div>
  | {data: None, error: None, loading: false} =>
    "I hope this is impossible, but sometimes it's not!"->React.string
  };
};

module AddTodoMutation = [%graphql
  {|
    mutation AddTodo($text: String!) {
      todo: addTodoSimple(text: $text) {
        id
        text
      }
    }
  |}
];

module TodosQuery = [%graphql
  {|
    query TodosQuery {
      todos: allTodos {
        id
        completed
        text
      }
    }
  |}
];

[@react.component]
let make = () => {
  let (mutate, result) = AddTodoMutation.use();

  switch (result) {
  | {called: false} =>
    <>
      "Not called... "->React.string
      <button
        onClick={_ =>
          mutate(
            ~refetchQueries=[|
              TodosQuery.refetchQueryDescription(),
              // - OR -
              String("TodosQuery") // Should rarely be needed?
            |],
            {text: "Another To-Do"},
          )
          ->ignore
        }>
        "Add To-Do"->React.string
      </button>
    </>
  | {loading: true} => "Loading..."->React.string
  | {data: Some({todo: {text}}), error: None} =>
    <p> {React.string("To-Do added: \"" ++ text ++ "\"")} </p>
  | {error} =>
    <>
      "Error loading data"->React.string
      {switch (error) {
       | Some(error) => React.string(": " ++ error.message)
       | None => React.null
       }}
    </>
  };
};

module Cache = ApolloClient.Cache;

module AddTodoMutation = [%graphql
  {|
    mutation AddTodo($text: String!) {
      todo: addTodoSimple(text: $text) {
        id
        completed
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
  let (text, setText) = React.useState(_ => "");

  let (mutate, result) = AddTodoMutation.use();
  let handleSubmit = event => {
    ReactEvent.Form.preventDefault(event);
    mutate({text: text})->ignore;
  };
  switch (result) {
  | {called: false} =>
    <>
      "Not called... "->React.string
      <form onSubmit=handleSubmit>
        <h2> {React.string("Add a new todo")} </h2>
        <div className="form-field">
          <input
            placeholder="Add Next ToDo"
            required=true
            value=text
            onChange={event => {
              let value = event->ReactEvent.Form.target##value;
              setText(value);
            }}
          />
        </div>
        <div className="form-field">
          <input type_="submit" value="Add To-Do" />
        </div>
      </form>
    </>
  | {loading: true} => "Loading..."->React.string
  | {data: Some({todo: {text, id}}), error: None} =>
    <div>
      <p> {React.string("To-Do added: \"" ++ text ++ "\"")} </p>
      <MutationDelete id />
    </div>
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

module Cache = ApolloClient.Cache;

module DeleteTodoMutation = [%graphql
  {|
      # This has to be ID! and not String! or it will fail silently
    mutation DeleteTodo ($id:ID!){
      deleteTodoItem(input: { id: $id }) {
        deletedTodoItemId
        clientMutationId
      }
    }
  |}
];

[@react.component]
let make = (~id: string) => {
  let (_, setId) = React.useState(_ => id);

  let (mutate, result) = DeleteTodoMutation.use();
  let handleSubmit = event => {
    ReactEvent.Form.preventDefault(event);
    mutate({id: id})->ignore;
  };
  switch (result) {
  | {called: false} =>
    <>
      "Not called... "->React.string
      <form onSubmit=handleSubmit>
        <h2> {React.string("Delete Id: " ++ id ++ "?")} </h2>
        <div className="form-field">
          <input
            placeholder=id
            value=id
            onChange={event => {
              let value = event->ReactEvent.Form.target##value;
              setId(value);
            }}
          />
        </div>
        <div className="form-field">
          <input type_="submit" value="Delete ToDo" />
        </div>
      </form>
    </>
  | {loading: true} => "Loading..."->React.string
  | {data: Some({deleteTodoItem}), error: None} =>
    let deletedTodoItemId =
      deleteTodoItem
      ->Belt.Option.map(d => d.deletedTodoItemId)
      ->Belt.Option.getWithDefault(Some(""));

    let deletedTodoItemId =
      switch (deletedTodoItemId) {
      | Some(id) => id
      | None => ""
      };
    <p> {React.string("To-Do id: \"" ++ deletedTodoItemId ++ "\" deleted")} </p>;
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

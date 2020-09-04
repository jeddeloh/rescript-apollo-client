// The TodosQuery below is going to look for a module of the same name to define the fragment
module TodoItem = Fragments.TodoItem;

module TodosQuery = [%graphql
  {|
    query TodosQuery {
      todos: allTodos {
        # This references the TodoItem fragment definition module above!
        ...TodoItem
      }
    }
  |}
];

// It's easy to share types when using Fragments
module TodoCount = {
  [@react.component]
  let make = (~todos: array(TodoItem.t)) => {
    <p>
      {React.string(
         "There are " ++ todos->Belt.Array.length->string_of_int ++ " To-Dos",
       )}
    </p>;
  };
};

[@react.component]
let make = () => {
  let queryResult = TodosQuery.use();

  <div>
    {switch (queryResult) {
     | {loading: true, data: None} => <p> "Loading"->React.string </p>
     | {loading, data: Some({todos}), error} =>
       <>
         <dialog>
           {loading ? <p> "Refreshing..."->React.string </p> : React.null}
           {switch (error) {
            | Some(_) =>
              <p>
                "Something went wrong, data may be incomplete"->React.string
              </p>
            | None => React.null
            }}
         </dialog>
         <TodoCount todos />
       </>
     | {loading: false, data: None} =>
       <p> "Error loading data"->React.string </p>
     }}
  </div>;
};

module TodosQuery = %graphql(
  `
    query TodosQuery {
      todos: allTodos {
        id
        text
        completed
      }
    }
  `
)

@react.component
let make = () => {
  let queryResult = TodosQuery.use()

  <div>
    {switch queryResult {
    | {loading: true, data: None} => <p> {"Loading"->React.string} </p>
    | {loading, data: Some({todos}), error, fetchMore} =>
      <div>
        <dialog>
          {loading ? <p> {"Refreshing..."->React.string} </p> : React.null}
          {switch error {
          | Some(_) => <p> {"Something went wrong, data may be incomplete"->React.string} </p>
          | None => React.null
          }}
        </dialog>
        <p>
          {React.string("There are " ++ (todos->Belt.Array.length->string_of_int ++ " To-Dos"))}
        </p>
        <p>
          <button
            onClick={_ => {
              fetchMore(~updateQuery=(previousData, {fetchMoreResult}) =>
                switch fetchMoreResult {
                | Some({todos: newTodos}) => {
                    todos: Belt.Array.concat(previousData.todos, newTodos),
                  }
                | None => previousData
                }
              , ())->Promise.map(result => {
                switch result {
                | Ok(_) => Js.log("fetchMore: success!")
                | Error(_) => Js.log("fetchMore: failure!")
                }
              })->ignore
            }}>
            {"Fetch More!"->React.string}
          </button>
        </p>
      </div>
    | {loading: false, data: None} => <p> {"Error loading data"->React.string} </p>
    }}
  </div>
}

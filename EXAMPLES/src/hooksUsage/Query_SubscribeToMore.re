module QueryResult = ApolloClient.Types.QueryResult;

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

module SorryItsNotASubscriptionForTodos = [%graphql
  {|
    subscription SorryItsNotASubscriptionForTodos {
      siteStatisticsUpdated {
        currentVisitorsOnline
      }
    }
  |}
];

[@react.component]
let make = () => {
  let queryResult = TodosQuery.use();

  /**
   * Sorry, this example is nonsensical given the current schema, but I'm gonna proceed anyway
   */
  React.useEffect0(() => {
    queryResult->QueryResult.subscribeToMore(
      ~subscription=(module SorryItsNotASubscriptionForTodos),
      ~updateQuery=
        (previous, {subscriptionData: {data: {siteStatisticsUpdated}}}) => {
          let count =
            siteStatisticsUpdated
            ->Belt.Option.map(stats => stats.currentVisitorsOnline)
            ->Belt.Option.getWithDefault(0)
            ->string_of_int;

          {
            todos:
              Belt.Array.concat(
                previous.todos,
                [|
                  {
                    __typename: "TodoItem",
                    id: "subscribeToMoreTodo",
                    completed: None,
                    text: "Hello, " ++ count ++ " vistors online",
                  },
                |],
              ),
          };
        },
      (),
    );
    None;
  });

  <>
    <p>
      "[ Not functional, but the examples are still valid ]"->React.string
    </p>
    {switch (queryResult) {
     | {data: Some({todos})} =>
       <p>
         {React.string(
            "There are "
            ++ todos->Belt.Array.length->string_of_int
            ++ " To-Dos",
          )}
       </p>
     | _ignoredForExample => React.null
     }}
  </>;
};

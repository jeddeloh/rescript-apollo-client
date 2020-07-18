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
  <>
    <p>
      "[ Not functional, but the examples are still valid ]"->React.string
    </p>
    {switch (SorryItsNotASubscriptionForTodos.use()) {
     | {data: Some({siteStatisticsUpdated: Some({currentVisitorsOnline})})} =>
       <p>
         {React.string(
            "There are "
            ++ string_of_int(currentVisitorsOnline)
            ++ " visitors online",
          )}
       </p>
     | _ignoredForExample => React.null
     }}
  </>;
};

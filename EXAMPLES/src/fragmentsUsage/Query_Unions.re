// The TodosQuery below is going to look for a module of the same name to define the fragment
module TicketFields = Union_Fragment.TicketFields;

module TicketQuery = [%graphql
  {|
    query TicketQuery {
      tickets (limit: 6, offset: 0)  {
        results {
          ...TicketFields
        }
      }
    }
  |}
];

// It's easy to share types when using Fragments
module TicketResultsComp = {
  [@react.component]
  let make = (~result: TicketFields.t) => {
    
    let ticketField = Client.instance.readFragment(
      ~fragment=(module Union_Fragment.TicketFields),
      ~id="Ticket" ++ ":" ++ result.id,
      ~fragmentName=("TicketFields"),
      (),
    );

    Js.log("ticketField");
    Js.log(ticketField);

    <div>
      {
        switch(ticketField){
        | None => <p>{ReasonReact.string("No Result")}</p>
        | Some({assignee: None}) => <p>{ReasonReact.string("No Result")}</p>
        | Some({assignee: Some(`User(user))}) => {
          Js.log("User");
          Js.log(user);
          <p>{ReasonReact.string("My Name is " ++ user.fullName)}</p>
        }
        | Some({assignee: Some(`WorkingGroup(workingGroup))}) => {
          Js.log("WorkingGroup");
          Js.log(workingGroup);
          <p>{ReasonReact.string("My dbId is " ++ workingGroup.dbId)}</p>
        }
        | Some({assignee: Some(`FutureAddedValue(_))}) => {
          Js.log("FutureAddedValue");
          Js.log(ticketField);
          <p>{ReasonReact.string("Future!!")}</p>
        }
        | _ => {
          Js.log("Everything else... shouldn't get here");
          <p>{ReasonReact.string("Something's wrong")}</p>
        }
        }
      }
    </div>;
  };
};

[@react.component]
let make = () => {
  let queryResult = TicketQuery.use();

  Js.log("queryResult");
  Js.log(queryResult);

  <div>
    {switch (queryResult) {
     | {loading: true, data: None} => <p> "Loading"->React.string </p>
     | {loading, data: Some({tickets}), error} =>
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
          {
            tickets.results
            |> Belt.Array.map(_, res => <TicketResultsComp key=res.id result=res />)
            |> ReasonReact.array
          }
       </>
     | {loading: false, data: None} =>
       <p> "Error loading data"->React.string </p>
     }}
  </div>;
};
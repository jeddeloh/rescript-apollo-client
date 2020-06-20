module AllPersonsQuery = [%graphql
  {|
  query AllPersonsQuery {
    allPersons {
      id
      name
    }
  }
|}
];

[@react.component]
let make = () => {
  let queryResult = AllPersonsQuery.use();
  <div>
    <h1> "Basic Query"->React.string </h1>
    <div>
      {switch (queryResult) {
       | {loading: true} => <p> "Loading..."->React.string </p>
       | {data: Some({allPersons}), error: None} =>
         <>
           <h3> "All people:"->React.string </h3>
           <ul>
             {allPersons
              ->Belt.Array.map(({name}) => <li> name->React.string </li>)
              ->React.array}
           </ul>
         </>
       | {loading: false, error} =>
         <>
           <div> "Error loading data:"->React.string </div>
           <div>
             {switch (error) {
              | Some(error) =>
                error
                ->Js.Json.stringifyAny
                ->Belt.Option.getWithDefault("[couldn't stringify error]")
                ->React.string
              | None => React.null
              }}
           </div>
         </>
       }}
    </div>
  </div>;
};
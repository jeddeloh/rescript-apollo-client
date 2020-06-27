module PeopleQuery = [%graphql
  {|
  query PeopleQuery {
    people: allPersons {
      id
      name
    }
  }
|}
];

[@react.component]
let make = () => {
  switch (PeopleQuery.use()) {
  | {loading: true} => "Loading..."->React.string
  | {error: Some(_error)} => "Error loading data"->React.string
  | {data: Some({people})} =>
    <h4>
      "There are "->React.string
      {people->Belt.Array.length->React.int}
      " people"->React.string
    </h4>
  | {data: None, error: None, loading: false} =>
    "I hope this is impossible, but sometimes it's not!"->React.string
  };
};

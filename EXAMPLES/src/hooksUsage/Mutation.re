module AddPersonMutation = [%graphql
  {|
    mutation addPerson($age: Int!, $name: String!) {
      person: createPerson(age: $age, name: $name) {
        id
        age
        name
      }
    }
  |}
];

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

module PersonsOlderThanQuery = [%graphql
  {|
  query getPersonsOlderThan($age: Int!) {
    allPersons(filter: { age_gte: $age } ) {
      id
    }
  }
|}
];

[@react.component]
let make = () => {
  let (mutate, result) = AddPersonMutation.use();

  switch (result) {
  | {called: false} =>
    <>
      "Not called... "->React.string
      <button
        onClick={_ =>
          mutate(
            ~refetchQueries=[|
              PeopleQuery.refetchQueryDescription(),
              // - OR -
              String("PeopleQuery") // Should rarely be needed?
            |],
            AddPersonMutation.makeVariables(~age=40, ~name="Jane", ()),
          )
          ->ignore
        }>
        "Add Person"->React.string
      </button>
    </>
  | {loading: true} => "Loading..."->React.string
  | {data: Some({person: Some(person)}), error: None} =>
    <h4> {React.string("Person added: " ++ person.name)} </h4>
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

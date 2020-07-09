module Prometo = Yawaramin__Prometo;

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

let logPeople_good_reasonPromise = _ =>
  Client.instance
  ->ApolloClient.query(~query=(module PeopleQuery), ())
  ->Promise.Js.fromBsPromise
  ->Promise.Js.toResult
  ->Promise.get(
      fun
      | Ok({data: Some({people})}) => Js.log2("Data: ", people)
      | Ok(_) => Js.log("Error: no people!")
      | Error(error) => Js.log2("Error: ", error),
    );

let logPeople_good_prometo = _ =>
  Client.instance
  ->ApolloClient.query(~query=(module PeopleQuery), ())
  ->Prometo.fromPromise
  ->Prometo.handle(~f=result => {
      switch (result) {
      | Ok({data: Some({people})}) => Js.log2("Data: ", people)
      | Ok(_) => Js.log("Error: no people!")
      | Error(error) => Js.log2("Error: ", error)
      };
      result;
    })
  ->ignore;

/**
 * The ergonomics of the Js module promise methods are such that the compiler cannot
 * infer the type of result which means the record fields are not in scope, forcing you
 * to annotate it. I would highly recommend using one of the promise libraries above!
 */
let logPeople_bad_jsPromise = _ =>
  Client.instance
  ->ApolloClient.query(~query=(module PeopleQuery), ())
  ->Js.Promise.then_(
      (result: ApolloClient__ApolloClient.ApolloQueryResult.t(_)) =>
        switch (result) {
        | {data: Some({PeopleQuery.people})} =>
          Js.Promise.resolve(Js.log2("Data: ", people))
        | _ => Js.Exn.raiseError("Error: no people!")
        },
      _,
    )
  ->Js.Promise.catch(
      eeyore => Js.Promise.resolve(Js.log2("Error: ", eeyore)),
      _,
    )
  ->ignore;

let addPerson = _ =>
  /**
   * If the operation module were not the last argument, we could just use a record here
   * instead of requiring the use of `makeVariables`. :thinking_face:
   */
  (
    Client.instance
    ->ApolloClient.mutate(
        ~mutation=(module AddPersonMutation),
        {age: 40, name: "Ted"},
      )
    ->Promise.Js.fromBsPromise
    ->Promise.Js.toResult
    ->Promise.get(
        fun
        | Ok(result) => Js.log2("Data: ", result.data)
        | Error(error) => Js.log2("Error: ", error),
      )
  );

[@react.component]
let make = () => {
  <div>
    <p>
      <button onClick=logPeople_good_reasonPromise>
        "Log People (Reason Promise)"->React.string
      </button>
    </p>
    <p>
      <button onClick=logPeople_good_prometo>
        "Log People (Prometo)"->React.string
      </button>
    </p>
    <p>
      <button onClick=logPeople_bad_jsPromise>
        "Log People (Js Module)"->React.string
      </button>
    </p>
    <p> <button onClick=addPerson> "Add Person"->React.string </button> </p>
  </div>;
};

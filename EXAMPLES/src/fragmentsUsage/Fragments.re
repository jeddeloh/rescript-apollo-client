[%graphql
  {|
    # Check it out! This will be exposed as a module called TodoItem!
    fragment TodoItem on TodoItem {
        id
        text
        completed
    }

    query Fragments {
      allTodos {
        ...TodoItem
      }
    }
  |};
  {inline: true}
];

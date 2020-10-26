module UserFields = [%graphql
  {|
    fragment UserFields on User {
      id
      avatarUrl
      fullName
    }
  |};
];

module WorkingGroupFields = [%graphql
  {|
    fragment WorkingGroupFields on WorkingGroup {
      id
      dbId
    }
  |};
];

module TicketFields = [%graphql
  {|
    fragment TicketFields on Ticket {
      id
      assignee {
        ... on User {
          ...UserFields
        }
        ... on WorkingGroup {
          ...WorkingGroupFields
        }
      }
    }
  |};
];

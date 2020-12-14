module NetworkStatus = {
  module Js_ = {
    type t = int
  }

  type t =
    | Loading
    | SetVariables
    | FetchMore
    | Refetch
    | Poll
    | Ready
    | Error
    | // Apollo types are not accurate. See:
    // https://github.com/reasonml-community/rescript-apollo-client/issues/68
    SkippedOrNotPresent

  let fromJs: Js_.t => t = js =>
    switch js {
    | 1 => Loading
    | 2 => SetVariables
    | 3 => FetchMore
    | 4 => Refetch
    | 6 => Poll
    | 7 => Ready
    | 8 => Error
    | _ => SkippedOrNotPresent
    }
}

module NetworkStatus = {
  module Js_ = {
    type t = int;
  };

  [@bs.deriving jsConverter]
  type t =
    | [@bs.as 1] Loading
    | [@bs.as 2] SetVariables
    | [@bs.as 3] FetchMore
    | [@bs.as 4] Refetch
    | [@bs.as 6] Poll
    | [@bs.as 7] Ready
    | [@bs.as 8] Error;

  let toJs: t => Js_.t = tToJs;

  let fromJs: Js_.t => t = string => tFromJs(string)->Belt.Option.getExn;
};

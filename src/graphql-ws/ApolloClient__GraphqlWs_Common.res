module MessageType = {
  module Js_ = {
    // /**
    //  * Types of messages allowed to be sent by the client/server over the WS protocol.
    //  *
    //  * @category Common
    //  */
    // export enum MessageType {
    //   ConnectionInit = 'connection_init', // Client -> Server
    //   ConnectionAck = 'connection_ack', // Server -> Client

    //   Ping = 'ping', // bidirectional
    //   Pong = 'pong', /// bidirectional

    //   Subscribe = 'subscribe', // Client -> Server
    //   Next = 'next', // Server -> Client
    //   Error = 'error', // Server -> Client
    //   Complete = 'complete', // bidirectional
    // }
    type t = string
  }

  type t =
    ConnectionInit | ConnectionAck | Ping | Pong | Subscribe | Next | Error | Complete | Unknown

  let fromJs: Js_.t => t = js =>
    switch js {
    | "connection_init" => ConnectionInit
    | "connection_ack" => ConnectionAck

    | "ping" => Ping
    | "pong" => Pong

    | "subscribe" => Subscribe
    | "next" => Next
    | "error" => Error
    | "complete" => Complete
    | _ => Unknown
    }
}

module Message = {
  module Js_ = {
    //  export type Message<T extends MessageType = MessageType> =
    //   T extends MessageType.ConnectionAck
    //     ? ConnectionAckMessage
    //     : T extends MessageType.ConnectionInit
    //       ? ConnectionInitMessage
    //       : T extends MessageType.Ping
    //         ? PingMessage
    //         : T extends MessageType.Pong
    //           ? PongMessage
    //           : T extends MessageType.Subscribe
    //             ? SubscribeMessage
    //             : T extends MessageType.Next
    //               ? NextMessage
    //               : T extends MessageType.Error
    //                 ? ErrorMessage
    //                 : T extends MessageType.Complete
    //                   ? CompleteMessage
    //                   : never;
    type t = {
      @as("type")
      type_: MessageType.t,
      payload?: Js.Dict.t<string>,
    }
  }

  type t = Js_.t
}

module SubscribePayload = {
  module Js_ = {
    //  export interface SubscribePayload {
    //   readonly operationName?: string | null | undefined;
    //   readonly query: string;
    //   readonly variables?: Record<string, unknown> | null | undefined;
    //   readonly extensions?: Record<string, unknown> | null | undefined;
    // }
    type t = {
      operationName?: string,
      query: string,
      variables?: Js.Dict.t<string>,
      extensions?: Js.Dict.t<string>,
    }
  }

  type t = Js_.t
}

/* export declare const throwServerError: (response: Response, result: any, message: string) => never */

module ServerError = {
  module Js_ = {
    // export declare type ServerError = Error & {
    //     response: Response;
    //     result: Record<string, any>;
    //     statusCode: number;
    // };
    type response

    type t = {
      response: response,
      result: Js.Json.t, // Actual: Record<string, any>;
      statusCode: int,
      // ...extends Error
      name: string,
      message: string,
      stack: option<string>,
    }
  }

  type t = Js_.t
}

// export declare function parseAndCheckHttpResponse(operations: Operation | Operation[]): (response: Response) => Promise<any>;
// export declare type ServerParseError = Error & {
//     response: Response;
//     statusCode: number;
//     bodyText: string;
/* } */

module ServerParseError = {
  module Js_ = {
    // export declare type ServerError = Error & {
    //     response: Response;
    //     result: Record<string, any>;
    //     statusCode: number;
    // };
    type response

    type t = {
      bodyText: string,
      response: response,
      statusCode: int,
      // ...extends Error
      name: string,
      message: string,
      stack: option<string>,
    }
  }

  type t = Js_.t
}

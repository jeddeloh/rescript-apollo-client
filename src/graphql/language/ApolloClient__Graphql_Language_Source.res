module Location = {
  type t = {
    line: int,
    column: int,
  }
}

module Source = {
  type t = {
    body: string,
    name: string,
    locationOffset: Location.t,
    //   constructor(body: string, name?: string, locationOffset?: Location);
  }
}

switch ReactDOM.querySelector("#root") {
| Some(el) =>
  ReactDOM.render(
    <React.StrictMode>
      <App />
    </React.StrictMode>,
    el,
  )
| None => ()
}

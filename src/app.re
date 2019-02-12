type route =
  | Login
  | Register
  | Score;

module App = {
  type state = {route};

  type action =
    | ChangeRoute(route);

  let reducer = (action, _state) =>
    switch (action) {
    | ChangeRoute(route) => ReasonReact.Update({route: route})
    };

  let mapUrlToRoute = (url: ReasonReact.Router.url) =>
    switch (url.path) {
    | ["login"] => Login
    | ["register"] => Register
    | ["score"] => Score
    | _ => Login
    };

  let component = ReasonReact.reducerComponent("App");

  let make = _children => {
    ...component,
    initialState: () => {route: ReasonReact.Router.dangerouslyGetInitialUrl() |> mapUrlToRoute},
    didMount: self => {
      let watchId = ReasonReact.Router.watchUrl(url => self.send(ChangeRoute(url |> mapUrlToRoute)));
      self.onUnmount(() => ReasonReact.Router.unwatchUrl(watchId));
    },
    reducer: (action, state) => {
      print_string("REDUCER");
      switch (action) {
      | ChangeRoute(route) => ReasonReact.Update({route: route})
      };
    },
    render: self =>
      switch (self.state.route) {
      | Register => <Register />
      | Login => <Login />
      | Score => <Score />
      },
  };
};

ReactDOMRe.renderToElementWithId(<App />, "main");

type route =
  | Login
  | Register;

module App = {
  type state = {route};

  type action =
    | ChangeRoute(route);

  let reducer = (action, _state) =>
    switch (action) {
    | ChangeRoute(route) => ReasonReact.Update({route: route})
    };

  let mapUrlToRoute = (url: ReasonReact.Router.url) => {
    print_string("test");
    switch (url.path) {
    | ["login"] => Login
    | ["register"] => Register
    | _ => Register
    };
  };

  let component = ReasonReact.reducerComponent("App");

  let make = _children => {
    ...component,
    initialState: () => {route: Login},
    didMount: self => {
      let watchId = ReasonReact.Router.watchUrl(url => self.send(ChangeRoute(url |> mapUrlToRoute)));
      self.onUnmount(() => ReasonReact.Router.unwatchUrl(watchId));
    },
    reducer: (action, state) =>
      switch (action) {
      | ChangeRoute(route) => ReasonReact.Update({route: route})
      },
    render: self =>
      switch (self.state.route) {
      | Register => <Register />
      | Login => <Login />
      | _ => <Register />
      },
  };
};

ReactDOMRe.renderToElementWithId(<App />, "main");

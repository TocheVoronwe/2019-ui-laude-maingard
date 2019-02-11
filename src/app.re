module App = {
  let component = ReasonReact.statelessComponent("App");
  let make = _children => {...component, render: _self => <Register />};
};

ReactDOMRe.renderToElementWithId(<Register />, "main");

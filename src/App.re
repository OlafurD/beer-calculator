open Css;

[%bs.raw {|require('./App.css')|}];

let app = style([textAlign(center)]);

let rotateAnim =
  keyframes([
    (0, [transform(rotate(deg(0)))]),
    (100, [transform(rotate(deg(360)))]),
  ]);

let appLogo =
  style([
    animation(
      ~duration=20000,
      ~timingFunction=linear,
      ~iterationCount=infinite,
      keyframes([
        (0, [transform(rotate(deg(0)))]),
        (100, [transform(rotate(deg(360)))]),
      ]),
    ),
    height(px(80)),
  ]);

[@bs.module] external logo : string = "./logo.svg";

type state = {grainWeight: int};

type action =
  | UpdateGrainWeight(string);

let component = ReasonReact.reducerComponent("App");

let typeInWeight = (weight, send) => send(UpdateGrainWeight(weight));

let make = (~message, _children) => {
  ...component,
  initialState: () => {grainWeight: 0},
  reducer: (action, state: state) =>
    switch (action) {
    | UpdateGrainWeight(newGrainWeight) =>
      let newWeight =
        if (newGrainWeight |> String.length == 0) {
          0;
        } else {
          newGrainWeight |> int_of_string;
        };
      ReasonReact.Update({grainWeight: newWeight});
    },
  render: self =>
    <div className=app>
      <div className="App-header">
        <img src=logo className=appLogo alt="logo" />
        <h2> (ReasonReact.string(message)) </h2>
      </div>
      <p className="App-intro">
        (ReasonReact.string("To get started, edit"))
        <code> (ReasonReact.string(" src/App.re ")) </code>
        (ReasonReact.string("and save to reload."))
      </p>
      <div>
        <span>
          (ReasonReact.string("Enter the weight of your grain: "))
        </span>
        <input
          _type="text"
          name="grain-weight"
          value=(self.state.grainWeight |> string_of_int)
          onChange=(
            ev =>
              typeInWeight(
                ReactDOMRe.domElementToObj(ReactEventRe.Form.target(ev))##value,
                self.send,
              )
          )
        />
      </div>
      <div>
        <span> (ReasonReact.string("You will need: ")) </span>
        <span>
          (
            ReasonReact.string(
              (self.state.grainWeight |> float_of_int)
              *. 2.7
              |> string_of_float,
            )
          )
        </span>
        <span> (ReasonReact.string(" liters of initial strike water")) </span>
      </div>
    </div>,
};
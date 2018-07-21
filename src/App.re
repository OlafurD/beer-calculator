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

type state = {
  grainWeight: int,
  grainTemp: int,
};

type action =
  | UpdateGrainWeight(string)
  | UpdateGrainTemp(string);

let component = ReasonReact.reducerComponent("App");
/*
 let wrapFailureInOption = (fn) =>
 try(fn()) {
 | exn => None
 }; */

let parseInput = (default, input) =>
  if (String.length(input) == 0) {
    0;
  } else {
    try (int_of_string(input)) {
    | exn => default
    };
  };

let dispatch = (send, action) => send(action);

let make = (~message, _children) => {
  ...component,
  initialState: () => {grainWeight: 0, grainTemp: 20},
  reducer: (action, state: state) =>
    switch (action) {
    | UpdateGrainTemp(newGrainTemp) =>
      Js.log("ABOUT TO UPDATE GRAIN TEMP");
      let parsedTemp = parseInput(state.grainTemp, newGrainTemp);
      ReasonReact.Update({...state, grainTemp: parsedTemp});
    | UpdateGrainWeight(newGrainWeight) =>
      let parsedWeight = parseInput(state.grainWeight, newGrainWeight);
      ReasonReact.Update({...state, grainWeight: parsedWeight});
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
        <div> <p> (ReasonReact.string("Beer parameters")) </p> </div>
        <FormInput
          fieldName="grain-weight (kg) : "
          action=(weight => UpdateGrainWeight(weight))
          value=self.state.grainWeight
          callback=(dispatch(self.send))
        />
        <FormInput
          fieldName="grain-temperature (C) : "
          action=(weight => UpdateGrainTemp(weight))
          value=self.state.grainTemp
          callback=(dispatch(self.send))
        />        
      </div>
      <div>
        <span> (ReasonReact.string("You will need: ")) </span>
        <span>
          (
            ReasonReact.string(
              float_of_int(self.state.grainWeight) *. 2.7 |> string_of_float,
            )
          )
        </span>
        <span> (ReasonReact.string(" liters of initial strike water")) </span>
      </div>
    </div>,
};
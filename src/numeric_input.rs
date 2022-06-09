use iced::pure::{button, column, row, text, text_input};
use iced::{Alignment, Length};
use iced_lazy::pure::{component, Component};
use iced_native::text;
use iced_pure::Element;

pub struct NumericInput<Msg> {
	value: u32,
	on_change: Box<dyn Fn(u32) -> Msg>,
}

#[derive(Debug, Clone)]
pub enum Event {
	InputChanged(String),
	IncrementPressed,
	DecrementPressed,
}

impl<Msg> NumericInput<Msg> {
	pub fn new(value: u32, on_change: impl Fn(u32) -> Msg + 'static) -> Self {
		Self {
			value,
			on_change: Box::new(on_change),
		}
	}
}

impl<Msg, Renderer> Component<Msg, Renderer> for NumericInput<Msg>
where
	Renderer: text::Renderer + 'static,
{
	type State = ();
	type Event = Event;

	fn update(&mut self, _state: &mut Self::State, event: Event) -> Option<Msg> {
		match event {
			Event::IncrementPressed => Some((self.on_change)(self.value.saturating_add(1))),
			Event::DecrementPressed => Some((self.on_change)(self.value.saturating_sub(1))),
			Event::InputChanged(value) => {
				if value.is_empty() {
					Some((self.on_change)(self.value))
				} else {
					value.parse().ok().map(self.on_change.as_ref())
				}
			}
		}
	}

	fn view(&self, _state: &Self::State) -> Element<Event, Renderer> {
		let button = |label, on_press| {
			button(
				text(label)
					.width(Length::Fill)
					.height(Length::Fill)
					.horizontal_alignment(iced_native::alignment::Horizontal::Center)
					.vertical_alignment(iced_native::alignment::Vertical::Center),
			)
			.width(Length::Units(50))
			.on_press(on_press)
		};

		row()
			.push(text_input(
				"Type a number",
				self.value.to_string().as_str(),
				Event::InputChanged,
			))
			.push(
				column()
					.push(button("-", Event::DecrementPressed))
					.push(button("+", Event::IncrementPressed)),
			)
			.align_items(Alignment::Fill)
			.into()
	}
}

impl<'a, Msg, Renderer> From<NumericInput<Msg>> for Element<'a, Msg, Renderer>
where
	Msg: 'a,
	Renderer: 'static + text::Renderer,
{
	fn from(numeric_input: NumericInput<Msg>) -> Self {
		component(numeric_input)
	}
}

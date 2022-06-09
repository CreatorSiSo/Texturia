use iced::pure::{container, row, Element, Sandbox};
use iced::*;
use std::path::Path;

mod utils;

// mod editor;
// use editor::*;

mod numeric_input;
use numeric_input::NumericInput;

fn main() -> iced::Result {
	match App::run(iced::Settings::default()) {
		Ok(_) => iced::Result::Ok(()),
		Err(error) => iced::Result::Err(error),
	}
}

#[derive(Debug)]
enum Message {
	ToggleDebug,
	NumericInputChanged(Option<u32>),
}

#[derive(Debug)]
struct App {
	current_file_path: &'static Path,
	saved: bool,
	// debug: bool,
}

impl Sandbox for App {
	type Message = Message;

	fn new() -> Self {
		App {
			current_file_path: Path::new("/test/dev/somethin/äöüdsffd/file.tex"),
			saved: false,
			// debug: false,
		}
	}

	fn title(&self) -> String {
		format!(
			"Texturia - {}{}",
			self.current_file_path.to_string_lossy(),
			if self.saved { "" } else { "*" }
		)
	}

	fn update(&mut self, message: Self::Message) {
		match message {
			Message::ToggleDebug => {}
			Message::NumericInputChanged(Some(new_value)) => println!("{new_value}"),
			_ => {}
		}
	}

	fn view(&self) -> Element<Self::Message> {
		container(NumericInput::new(Some(20), Message::NumericInputChanged))
			.width(Length::Fill)
			.height(Length::Fill)
			.padding(Padding::new(5))
			.into()
	}

	fn background_color(&self) -> Color {
		Color::from_rgb(0.1, 0.1, 0.1)
	}
}

struct ContainerStyle {}

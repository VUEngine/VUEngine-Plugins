<template>
	<v-form>

		<v-row>
			<v-col>

				<s-data-table
					:data.sync="data.data.config.project.i18n.languages"
					:compare="data.lastSavedData.config.project.i18n.languages"
					:i18n="i18n"
					:fields="fields"
					draggable=true
					label="First language is the default one."
				></s-data-table>

			</v-col>
		</v-row>

	</v-form>
</template>

<script>
	module.exports = {
		props: [
			'data',
			'i18n'
		],
		data: () => ({
			fields: [
				{
					label: 'ID',
					key: 'id'
				},
				{
					label: 'Name',
					key: 'name'
				},
				{
					label: 'Flag Entity',
					key: 'flag'
				},
			]
		}),
		methods: {
			onDataChanged() {
				this.updateStrings()
			},
			updateStrings() {
				let filteredStrings = [];

				// get a sorted list of languages so the order of translations under "strings" won't depend on the order of languages
				let languages = []
				for (let language of this.data.data.config.project.i18n.languages) {
					languages.push(language.id)
				}
				languages.sort()

				for (let string of this.data.data.config.project.i18n.strings) {
					let filteredString = {
						"id": string.id,
						"translations": []
					};
					for (let language of languages) {
						let filteredTranslation = {
							language: language,
							translation: ''
						}
						for (let translation of string.translations) {
							if (translation.language == language) {
								filteredTranslation.translation = translation.translation
							}
						}
						filteredString.translations.push(filteredTranslation)
					}
					filteredStrings.push(filteredString);
				}

				this.data.data.config.project.i18n.strings = filteredStrings
			}
		},
		watch: {
			'data.data.config.project.i18n.languages': {
				handler: function (val, oldVal) {
					this.onDataChanged();
				},
				deep: true
			}
		}
	}
</script>

<style scoped>
</style>
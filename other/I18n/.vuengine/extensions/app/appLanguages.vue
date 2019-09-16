<template>
	<v-form>

		<v-row>
			<v-col>
				First language is the default one.
			</v-col>
		</v-row>

		<v-row>
			<v-col>

				<s-data-table
					:data.sync="data.config.project.i18n.languages"
					:compare="data.lastSavedConfig.project.i18n.languages"
					:i18n="i18n"
					:fields="fields"
					draggable=true
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
		})
	}
</script>

<style scoped>
</style>